import sys
import json
from typing import List, Dict, Union


class Variable:

    def __init__(self, varname: str, funcname: str, depth: int, offset: int, vartype: str, globl: bool = False) -> None:
        self.varname = varname
        self.funcname = funcname
        self.depth = depth
        self.offset = offset
        self.vartype = vartype
        self.globl = globl

    def location(self):
        if self.globl:
            return f"{self.varname}(%rip)"
        else:
            return f"{self.offset}(%rbp)"
    
    def __repr__(self) -> str:
        return "v(" + self.varname + ", " + str(self.offset) + ", " + self.vartype + ")"

    def __str__(self) -> str:
        return self.__repr__()



class Function:

    def __init__(self, name: str, arguments: List[int], return_type: str) -> None:
        pass


class AssemblyFile:

    def __init__(self) -> None:
        
        self.own_asm = ""

        template = "template.s"
        if len(sys.argv) >= 3:
            template = sys.argv[2]
        
        with open(template, "r") as f:
            self.own_asm += f.read()

        self.current_section = "text"


    def add(self, content, **kwargs):
        
        if isinstance(content, list):
            for line in content:
                self.add(line, **kwargs)
            return

        indent = "\t"
        if "indent" in kwargs and not kwargs["indent"]:
            indent = ""

        self.own_asm += indent + content + "\n"


    def set_section(self, section):
        
        if section == self.current_section:
            return
        
        need_return = '\n' if self.own_asm != "" else ""
        self.add(f"{need_return}\t.{section}", indent=False)
        self.current_section = section


# VARIABLES = {}
VARIABLES: List[Dict[str, Variable]] = [{}]
VARIABLE_OFFSET = 0
FUNCTIONS = {}

VAR_SZ = 8
COMMENT = '#'



def variable_id(name, funcname, depth):
    return name + "-" + funcname + "-" + str(depth)


def get_variable_object_via_json(element, funcname: str, depth: int) -> Variable:

    if element["action"] == "varget":
        return get_variable_object(element["name"], funcname, depth)


def get_variable_location_via_json(element, funcname: str, depth: int):

    if element["action"] == "varget":
        return get_variable_location(element["name"], funcname, depth)


def get_variable_object(varname: str, funcname: str, depth: int) -> Variable:

    global VARIABLES
    depth_iterator = depth

    while depth_iterator >= 0:
        var_id = variable_id(varname, funcname, depth_iterator)
        if var_id in VARIABLES[depth_iterator] or varname in VARIABLES[depth_iterator]:
            return VARIABLES[depth_iterator][var_id]
        depth_iterator -= 1
        
    raise Exception(f"Undefined Variable {var_id}/{varname}")
    # return f"{varname}(%rip)"



def get_variable_location(varname: str, funcname: str, depth: int):

    obj = get_variable_object(varname, funcname, depth)

    if obj.globl:
        return f"{obj.varname}(%rip)"
    else:
        return f"{obj.offset}(%rbp)"



    global VARIABLES
    depth_iterator = depth

    while depth_iterator >= 0:
        var_id = variable_id(varname, funcname, depth_iterator)
        if var_id in VARIABLES[depth_iterator]:
            offset_to_rbp = VARIABLES[depth_iterator][var_id].offset
            return f"{offset_to_rbp}(%rbp)"
        depth_iterator -= 1
        
    return f"{varname}"


def get_variable(varname: str, funcname: str, depth: int):

    location = get_variable_location(varname, funcname, depth)
    push_location(location, f"push variable {varname}")



def push_location(location: str, comment: str = "Default comment :')"):

    asm.add([
        f"{COMMENT} variable expr",
        f"push {location}",
        ""
    ])


def end_function_here():
    asm.add([
        "mov %rbp, %rsp",
        "pop %rbp",
        "ret",
        ""
    ])


def write_scope(scope, depth: int):
    pass


def evaluate_scope(body, funcname, return_type, depth):

    global VARIABLES, VARIABLE_OFFSET

    for element in body:
        
        if element["action"] == "return":
            if len(element["value"].keys()) != 0:
                evaluate_expression(element["value"], funcname, depth)
            end_function_here()
            continue

        if element["action"] == "expr":
            evaluate_expression(element["value"], funcname, depth)
            continue

        if element["action"] == "vardef":
            varname = element['name']
            vartype = element['type']
            var_id = variable_id(varname, funcname, depth)
            
            var_size = VAR_SZ
            
            asm.add([
                f"{COMMENT} space for var {var_id}, type {vartype}",
                f"sub ${var_size}, %rsp",
                ""
            ])

            VARIABLE_OFFSET += var_size
            # VARIABLES[depth][var_id] = (var_id, -VARIABLE_OFFSET, vartype)
            VARIABLES[depth][var_id] = Variable(varname, funcname, depth, -VARIABLE_OFFSET, vartype)

            if len(element["value"].keys()) > 0:
                rebuild_varset = {'action': 'varset', 'left_value': {'action': 'varget', 'name': varname}, 'op': '=', 'value': element['value']}
                evaluate_scope([rebuild_varset], funcname, return_type, depth)

            continue

        if element["action"] == "varset":

            evaluate_expression(element['value'], funcname, depth)
            var_obj = get_variable_object_via_json(element["left_value"], funcname, depth)
            location = var_obj.location()
            vartype = var_obj.vartype
            # vartype = get_variable_location_via_json(element["left_value"], funcname, depth)
            
            asm.add([
                f"{COMMENT} varset left_value, for type {vartype}",
                f"pop %rax"
            ])

            asm.add([f"mov %rax, {location}"])
            asm.add("")

            # if vartype in ["int", "float"]:
            #     asm.add(f"mov %rax, {location}")
            # elif vartype in ["bool"]:
            #     asm.add(f"mov byte") 


            # print(var_obj)
            continue

        if element["action"] == "for":
            pass

        # print(element)

        
def define_function(funcname, return_type, arguments, scope, added):

    global VARIABLES, VARIABLE_OFFSET
    
    current_depth = 1
    VARIABLES.append({})

    asm.set_section("text")
    
    asm.add(f"{funcname}:", indent=False)
    asm.add([
        "push %rbp",
        "mov %rsp, %rbp",
        ""
    ])

    arg_count = len(arguments)
    for i, arg in enumerate(arguments):
        
        if arg["action"] != "arg":
            continue
        
        arg_type = arg["type"]
        arg_name = arg["name"]

        var_id = variable_id(arg_name, funcname, current_depth)
        VARIABLES[current_depth][var_id] = Variable(var_id, funcname, current_depth, 8 * (1 + (arg_count - i)), arg_type)

    evaluate_scope(scope["body"], funcname, return_type, current_depth)
    end_function_here()

    VARIABLES.pop()




def evaluate_expression(expr, funcname, depth: int):

    operators = {
        "+": "add %rax, %rbx",
        "-": "sub %rbx, %rax\n\tmov %rax, %rbx",
        "*": "imul %rax, %rbx",
        "/": "cqo\n\tidivq %rbx\n\tmov %rax, %rbx",
        "%": "xor %rdx, %rdx\n\tidivq %rbx\n\tmov %rdx, %rbx",
        "&&": "and %rax, %rbx",
        "||": "or %rax, %rbx",
        "&": "and %rax, %rbx",
        "|": "or %rax, %rbx"
    }

    if expr["action"] == "var":
        get_variable(expr["name"], funcname, depth)
        return
    
    if expr["action"] == "valueget":
        location = get_variable_location_via_json(expr["value"], funcname, depth)
        push_location(location, "pushing var through valueget")
        return

    if expr["action"] == "funcall":
        
        # total_arg_size = 

        arg_count = len(expr["args"])
        for arg in expr["args"]:
            evaluate_expression(arg, funcname, depth)
            # var_size = get_argument_size(arg)
            # print(arg)
        

        asm.add([
            f"{COMMENT} function call",
            f"call {expr['name']}",
            f"add ${VAR_SZ * arg_count}, %rsp",
            "push %rax",
            ""
        ])
        return
    
    if expr["action"] == "const":
        evaluate_expression(expr["value"], funcname, depth)
        return

    if expr["action"] == "int":
        asm.add([
            f"{COMMENT} push const int",
            f"push ${expr['value']}",
            ""
        ])
        return

    if expr["action"] == "varget":
        evaluate_expression(expr['value'], funcname, depth)
        return

    if expr["action"] == "litteral":
        evaluate_expression(expr["value"], funcname, depth)
        return

    if expr["action"] == "binop":
        
        evaluate_expression(expr["v1"], funcname, depth)
        evaluate_expression(expr["v2"], funcname, depth)

        asm.add([
            f"{COMMENT} {expr['binop']}",
            "pop %rbx",
            "pop %rax",
            operators[expr['binop']],
            "push %rbx",
            ""
        ])
        return

    if expr["action"] == "bool":
        asm.add([
            f"{COMMENT} push const bool",
            f"push ${'1' if expr['value'] else '0'}",
            ""
        ])

    # print(expr)

        



        




if __name__ == "__main__":

    if len(sys.argv) < 2:
        raise Exception("Missing a filename.json to open")

    with open(sys.argv[1], "r") as f:
        data = json.load(f)

    asm = AssemblyFile()

    to_add_when_calling = []
    for element in data:
        
        if element["action"] == "gvardef":
            asm.set_section("bss")
            asm.add([
                f".align {VAR_SZ}",
                f".type {element['name']}, @object",
                f".size {element['name']}, {VAR_SZ}"
            ])
            asm.add(f"{element['name']}:", indent=False)
            asm.add(f".zero {VAR_SZ}")
            continue

        if element["action"] == "varset":
            to_add_when_calling.append(element)
            continue

        if element["action"] == "fundef":
            scope = element["body"]
            # body = scope["body"]
            if element["name"] == "main":
                appened = to_add_when_calling
            else:
                appened = None
            define_function(element["name"], element["type"], element["args"], scope, appened)
            continue

    with open(sys.argv[1].replace(".json", ".s"), "w") as f:
        f.write(asm.own_asm)    


