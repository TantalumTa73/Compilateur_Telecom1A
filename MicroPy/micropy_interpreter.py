import json
import sys
import time


cur_vars = [{}]
cur_funcs = {}

LAST_IF_VALUE = [False]


class ReturnException(Exception):
    
    def __init__(self, return_value) -> None:
        super().__init__(return_value)


class Variable:

    def __init__(self, value, inherit_from = None, index: int = 0) -> None:
        self.value = value
        self.is_global = False
        self.inherit_from = inherit_from
        self.index = index

    def vget(self):

        r_value = self.value

        if self.inherit_from is not None:
            r_value = self.inherit_from.vget()[self.index]

        if r_value is None:
            raise UnboundLocalError(f"local variable referenced before assignement")
        
        return r_value
    
    def vset(self, new_value):

        self.inherit_from: Variable
        if self.inherit_from is not None:
            previous_array = self.inherit_from.vget()
            previous_array[self.index] = new_value

        self.value = new_value

    def __repr__(self) -> str:
        return "v." + str(self.value)
    
    def __str__(self) -> str:
        return self.__repr__()

    def set_global(self):
        self.is_global = True
    
    def set_non_global(self):
        self.is_global = False



def get_variable_object(data, depth: int, to_be_modified: bool = False):
    
    # print(1)

    if data["type"] == "array access":

        obj = get_variable_object(data["array"], depth, to_be_modified)
        array_index = evaluate_expression(data["index"], depth)
        return Variable(None, obj, array_index)

    
    if data["type"] == "var":

        varname = data["name"]
        # print(varname, depth)
        if depth < len(cur_vars) and varname in cur_vars[depth]:
            return cur_vars[depth][varname] 
        
        if varname in cur_vars[0] and ((not to_be_modified) or cur_vars[0][varname].is_global):
            return cur_vars[0][varname]

        cur_vars[depth][varname] = Variable(None)
        return cur_vars[depth][varname]
    
    if data["type"] == "left_value":

        return get_variable_object(data["value"], depth, to_be_modified)


def evaluate_expression(expr, depth: int): #A modifier pour cpp
    operators = {
        "Add": lambda x, y: x + y,
        "Sub": lambda x, y: x - y,
        "Mul": lambda x, y: x * y,
        "Div": lambda x, y: x // y,
        "Mod": lambda x, y: x % y,
        "==": lambda x, y: x == y,
        "!=": lambda x, y: x != y,
        ">=": lambda x, y: x >= y,
        "<=": lambda x, y: x <= y,
        ">": lambda x, y: x > y,
        "<": lambda x, y: x < y,
        "&&": lambda x, y: x and y,
        "||": lambda x, y: x or y,
    }

    if expr["type"] == "not":
        return not evaluate_expression(expr["value"], depth)

    if expr["type"] == "binop":
        v1 = evaluate_expression(expr["v1"], depth)
        v2 = evaluate_expression(expr["v2"], depth)
        # print(expr["v1"], v1, v2)
        return operators[expr["binop"]](v1, v2)
    
    if expr["type"] == "const":
        return evaluate_expression(expr["value"], depth)
    
    if expr["type"] == "moins":
        return -evaluate_expression(expr["value"], depth)

    if expr["type"] == "int":
        return expr["value"]
    
    if expr["type"] == "bool":
        return expr["value"]
    
    if expr["type"] == "string":
        return expr["value"]
    
    if expr["type"] == "none":
        return None
    
    if expr["type"] == "list":
        return [evaluate_expression(x, depth) for x in expr["content"]]

    if expr["type"] == "var":
        # print(expr, cur_vars, depth)
        return get_variable_object(expr, depth).vget()
    
    if expr["type"] == "left_value":
        return evaluate_expression(expr["value"], depth)
    
    if expr["type"] == "array access":
        array_object = get_variable_object(expr["array"], depth)
        return array_object.vget()[evaluate_expression(expr["index"], depth)]

    if expr["type"] == "call":
        args = [evaluate_expression(x, depth) for x in expr["args"]]
        return evaluate_function(expr["funname"], args, depth + 1)


def evaluate(line, depth: int):

    global LAST_IF_VALUE
    # print(line["type"], line.keys())

    if line["type"] == "fundef":
        cur_funcs[line["name"]] = (line["args"], line["body"])
        return
    
    if line["type"] == "stmt":
        return evaluate(line["stmt"], depth)
    
    if line["type"] == "stmt list":

        LAST_IF_VALUE.append(False)
        for stmt in line["body"]:
            try:
                evaluate(stmt, depth)
            except ReturnException as r:
                LAST_IF_VALUE.pop()
                raise r

        LAST_IF_VALUE.pop()
        return
    
    if line["type"] == "varset":
        var = get_variable_object(line["left_value"], depth, True)
        value = evaluate_expression(line["value"], depth)
        var.vset(value)
        return True
    
    if line["type"] == "expr":
        return evaluate(line["value"], depth)
    
    if line["type"] == "call":

        funname = line["funname"]
        args = [evaluate_expression(x, depth) for x in line["args"]]

        if funname == "print": #A modifier pour cpp
            print(*args)
            return 

        return evaluate_function(funname, args, depth + 1)
    
    if line["type"] == "return":
        return_value = evaluate_expression(line["value"], depth)
        raise ReturnException(return_value)

    if line["type"] == "for":

        var = line["varname"]
        given_set = evaluate_expression(line["in_set"], depth)
        set_length = len(given_set)

        cur_vars[depth][var] = Variable(None)
        var_object = cur_vars[depth][var]

        for i in range(set_length):
            var_object.vset(given_set[i])
            evaluate(line["body"], depth)

    if line["type"] == "if":
        condition = evaluate_expression(line["condition"], depth)
        LAST_IF_VALUE[-1] = condition
        if condition:
            evaluate(line["body"], depth)
        return

    if line["type"] == "elif":
        # print(LAST_IF_VALUE)
        if LAST_IF_VALUE[-1]:
            return
        condition = evaluate_expression(line["condition"], depth)
        LAST_IF_VALUE[-1] = condition
        if condition:
            evaluate(line["body"], depth)
        return
    
    if line["type"] == "else":
        if LAST_IF_VALUE[-1]:
            return
        evaluate(line["body"], depth)

    if line["type"] == "while":
    
        while evaluate_expression(line["condition"], depth):
            evaluate(line["body"], depth)





def evaluate_function(name, args, depth: int):

    # print(name, args, depth)

    if name == "len":
        return len(args[0])
    
    if name == "type":
        if isinstance(args[0], int):
            return "int"
        if isinstance(args[0], str):
            return "string"
        if isinstance(args[0], list):
            return "list"
        if isinstance(args[0], bool):   
            return "bool"

    cur_vars.append({})
    LAST_IF_VALUE.append(False)

    arg_names, func_json = cur_funcs[name]
    for arg_name, arg_value in zip(arg_names, args):
        cur_vars[depth][arg_name] = Variable(arg_value)

    # print(cur_vars)
    for line in func_json["body"]:

        try:
            evaluate(line, depth)
        except ReturnException as r:
            cur_vars.pop()
            LAST_IF_VALUE.pop()
            return r.args[0]

    cur_vars.pop()
    LAST_IF_VALUE.pop()





if __name__ == "__main__":

    with open(sys.argv[1], "r") as f:
        data = json.load(f)

    for line in data:
        evaluate(line, 0)

    # print(cur_vars)


    
