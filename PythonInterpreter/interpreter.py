import json
import sys


variables = {}
local_variables = []
functions = {}


class Function:

    def __init__(self, name: str, arg: str, body: list):
        self.name = name
        self.arg = arg
        self.body = body


def call_function(func_name, argument):

    if func_name == "print":
        print(argument)
        # print(variables, local_variables)
        return
    
    f: Function = functions[func_name]
    local_variables.append({f.arg: argument})
    # print("+++++++++++++++++++", f.arg, argument)

    for element in f.body:

        # print(element)

        if "action" in element:

            if element["action"] == "gvardef":

                var_name = element["name"]
                local_variables[-1][var_name] = None

            if element["action"] == "varset":

                var_name = element["name"]
                if var_name in local_variables[-1]:
                    local_variables[-1][var_name] = eval_expr(element["expr"])
                elif var_name in variables:
                    variables[var_name] = eval_expr(element["expr"])
                else:
                    raise Exception(f"variable {var_name} was never initialized")
    
            if element["action"] == "return":
                ret_value = eval_expr(element["expr"])
                local_variables.pop()
                return ret_value 
            
            if element["action"] == "function":
                call_function(element["name"], eval_expr(element["expr"]))
            
    local_variables.pop()
    





def eval_expr(expr):

    if "action" in expr:
        if expr["action"] == "function":
            return call_function(expr["name"], eval_expr(expr["expr"]))  

    if "type" not in expr:
        raise Exception("expr should have a type if it is not a function")

    if expr["type"] == "opposite":
        return -eval_expr(expr["expr"])

    operators = {
        "plus": lambda x, y: x + y,
        "minus": lambda x, y: x - y,
        "mult": lambda x, y: x * y,
        "division": lambda x, y: x // y,
        "modulo": lambda x, y: x % y,
    }

    if expr["type"] == "operation":
        l_eval = eval_expr(expr["left"])
        r_eval = eval_expr(expr["right"])
        return operators[expr["operator"]](l_eval, r_eval)
        
    if expr["type"] == "cst": 
        return expr["value"]
    
    if expr["type"] == "parenthesis":
        return eval_expr(expr["inner"])
        
    if expr["type"] == "var":
        
        var_name = expr["name"]
        if var_name in local_variables[-1]:
            return local_variables[-1][var_name]
        elif var_name in variables:
            return variables[var_name]
        else:
            print()
            raise Exception(f"Variable {var_name} has never been defined before", expr["start_line"])




if __name__ == "__main__":
    
    if len(sys.argv) < 2:
        raise Exception("Missing filename.json as argument")
    
    filename = sys.argv[1]

    with open(filename, "r") as f:
        data = json.load(f)

    for element in data:
        
        if "action" in element:

            if element["action"] == "gvardef":
                variables[element["name"]] = None
            
            if element["action"] == "gfundef":
                functions[element["name"]] = Function(element["name"], element["arg"], element["body"])

            if element["action"] == "varset":
                variables[element["name"]] = eval_expr(element["expr"])

    if "main" not in functions:
        raise Exception("main function was never defined")

    call_function("main", 0)

    # print(variables, functions)