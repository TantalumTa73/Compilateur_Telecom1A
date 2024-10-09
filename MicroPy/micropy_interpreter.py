import json
import sys
import time


cur_vars = [{}]
cur_funcs = {}

class Variable:

    def __init__(self, value) -> None:
        self.value = value
        self.can_be_modified = False

    def vget(self):
        return self.value
    
    def vset(self, new_value):
        self.value = new_value

    def __repr__(self) -> str:
        return str(self.value)
    
    def __str__(self) -> str:
        return self.__repr__()

    def set_global(self):
        self.can_be_modified = True
    
    def set_non_global(self):
        self.can_be_modified = False



def get_variable_object(data, scope: int = 0, to_be_modified = False):

    # print(data)
    
    if data["type"] == "var":
        
        varname = data["name"]
        if scope < len(cur_vars) and varname in cur_vars[scope]:
            return cur_vars[scope][varname] 
        elif varname in cur_vars[0] and (not to_be_modified or cur_vars[0][varname].can_be_modified):
            return cur_vars[0][varname]
        else:
            cur_vars[scope][varname] = Variable(None)
            return cur_vars[scope][varname]



# def set_variable(data, value, scope: int = 0):

#     if data["type"] == "array access":
#         return 

#     if scope < len(current_variables) and name in current_variables[scope]:
#         current_variables[scope][name].vset(value)
#     elif name in current_variables[0] and current_variables[0][name].can_be_modified:
#         current_variables[0][name].vset(value)
#     else:
#         current_variables[scope][name] = Variable(value)


# def get_variable(name: int, scope: int = 0):

#     if scope < len(current_variables) and name in current_variables[scope]:
#         current_variables[scope][name].vget()
#     elif name in current_variables[0]:
#         current_variables[0][name].vget()



def evaluate_expression(expr):

    operators = {
        "Add": lambda x, y: x + y,
        "Sub": lambda x, y: x - y,
        "Mul": lambda x, y: x * y,
        "Div": lambda x, y: x // y,
    }

    if expr["type"] == "binop":
        v1 = evaluate_expression(expr["v1"])
        v2 = evaluate_expression(expr["v2"])
        return operators[expr["binop"]](v1, v2)
    
    if expr["type"] == "const":
        return evaluate_expression(expr["value"])
    
    if expr["type"] == "int":
        return expr["value"]
    
    if expr["type"] == "list":
        return [evaluate_expression(x) for x in expr["content"]]

    if expr["type"] == "var":
        # print("aaaaaaa", expr)
        return get_variable_object(expr).vget()
    
    if expr["type"] == "left_value":
        return evaluate_expression(expr["value"])
    
    if expr["type"] == "array access":
        # print(expr)
        array_object = get_variable_object(expr["array"])
        return array_object.vget()[evaluate_expression(expr["index"])]


def evaluate(line, depth: int = 0):

    if line["type"] == "fundef":
        cur_funcs[line["name"]] = (line["args"], line["body"])
        return
    
    if line["type"] == "stmt":
        return evaluate(line["stmt"])
    
    if line["type"] == "varset":
        # print(line.keys())
        var = get_variable_object(line["left_value"], depth, True)
        value = evaluate_expression(line["value"])
        var.vset(value)
        # set_variable(line["name"], evaluate_expression(line["value"]))
        return
    
    if line["type"] == "expr":
        return evaluate(line["value"])
    
    if line["type"] == "call":

        # print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAaaaa", line)
        # print("6+++++++++++++++++++", line)

        if line["funname"] == "print":
            print(*[evaluate_expression(x) for x in line["args"]])
            return

        # return evaluate_expression(line["expr"])
    




if __name__ == "__main__":

    with open(sys.argv[1], "r") as f:
        data = json.load(f)

    for line in data:
        evaluate(line)

    # print(cur_vars)


    
