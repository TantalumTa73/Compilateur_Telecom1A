import json
import sys
import time


cur_vars = [{}]
cur_funcs = {}


class ReturnException(Exception):
    
    def __init__(self, return_value) -> None:
        super().__init__(return_value)


class Variable:

    def __init__(self, value, inherit_from = None, index: int = 0) -> None:
        self.value = value
        self.can_be_modified = False
        self.inherit_from = inherit_from
        self.index = index

    def vget(self):

        if self.inherit_from is not None:
            return self.inherit_from.vget()[self.index]

        return self.value
    
    def vset(self, new_value):

        self.inherit_from: Variable
        if self.inherit_from is not None:
            previous_array = self.inherit_from.vget()
            previous_array[self.index] = new_value

        self.value = new_value

    def __repr__(self) -> str:
        return str(self.value)
    
    def __str__(self) -> str:
        return self.__repr__()

    def set_global(self):
        self.can_be_modified = True
    
    def set_non_global(self):
        self.can_be_modified = False



def get_variable_object(data, depth: int = 0, to_be_modified = False):

    if data["type"] == "array access":

        obj = get_variable_object(data["array"], depth, to_be_modified)
        array_index = evaluate_expression(data["index"], depth)
        return Variable(None, obj, array_index)

    
    if data["type"] == "var":
        
        varname = data["name"]
        if depth < len(cur_vars) and varname in cur_vars[depth]:
            return cur_vars[depth][varname] 
        elif varname in cur_vars[0] and (not to_be_modified or cur_vars[0][varname].can_be_modified):
            return cur_vars[0][varname]
        else:
            cur_vars[depth][varname] = Variable(None)
            return cur_vars[depth][varname]


def evaluate_expression(expr, depth: int = 0):

    operators = {
        "Add": lambda x, y: x + y,
        "Sub": lambda x, y: x - y,
        "Mul": lambda x, y: x * y,
        "Div": lambda x, y: x // y,
        "Mod": lambda x, y: x % y,
        "==": lambda x, y: x == y,
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
        return operators[expr["binop"]](v1, v2)
    
    if expr["type"] == "const":
        return evaluate_expression(expr["value"], depth)
    
    if expr["type"] == "int":
        return expr["value"]
    
    if expr["type"] == "bool":
        return expr["value"]
    
    if expr["type"] == "string":
        return expr["value"]
    
    if expr["type"] == "list":
        return [evaluate_expression(x, depth) for x in expr["content"]]

    if expr["type"] == "var":
        return get_variable_object(expr, depth).vget()
    
    if expr["type"] == "left_value":
        return evaluate_expression(expr["value"], depth)
    
    if expr["type"] == "array access":
        array_object = get_variable_object(expr["array"])
        return array_object.vget()[evaluate_expression(expr["index"], depth)]

    if expr["type"] == "call":
        args = [evaluate_expression(x) for x in expr["args"]]
        return evaluate_function(expr["funname"], args, depth + 1)


def evaluate(line, depth: int = 0):

    if line["type"] == "fundef":
        cur_funcs[line["name"]] = (line["args"], line["body"])
        return
    
    if line["type"] == "stmt":
        return evaluate(line["stmt"])
    
    if line["type"] == "stmt list":
        for stmt in line["body"]:
            evaluate(stmt, depth)
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

        if funname == "print":
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



def evaluate_function(name, args, depth: int = 0):

    cur_vars.append({})

    arg_names, func_json = cur_funcs[name]
    for arg_name, arg_value in zip(arg_names, args):
        cur_vars[depth][arg_name] = Variable(arg_value)

    for line in func_json["body"]:

        try:
            evaluate(line, depth)
        except ReturnException as r:
            return r.args[0]


    cur_vars.pop()





if __name__ == "__main__":

    with open(sys.argv[1], "r") as f:
        data = json.load(f)

    for line in data:
        evaluate(line)

    # print(cur_vars)


    
