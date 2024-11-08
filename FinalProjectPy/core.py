import sys
import json
from typing import List, Dict
import math


class Variable:


    def __init__(self, varname: str, funcname: str, depth: int, offset: int, vartype: str, globl: bool = False, unreference: int = 0) -> None:
        self.varname = varname
        self.funcname = funcname
        self.depth = depth
        self.offset = offset
        self.vartype = vartype
        self.globl = globl
        self.unreference = unreference


    def location(self):
        if self.globl:
            return f"{self.varname}(%rip)"
        else:
            return f"{self.offset}(%rbp)"
    

    def __repr__(self) -> str:
        return "v(" + self.varname + ", " + str(self.offset) + ", " + self.vartype + ")"


    def __str__(self) -> str:
        return self.__repr__()


# class ArrayAccess:

#     def __init__(self, array: Variable, index: tuple) -> None:
#         self.array: Variable = array
#         self.index = index

    

# class Function:

#     def __init__(self, name: str, arguments: List[int], return_type: str) -> None:
#         pass


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

LOOP_IDENTIFIER = 0
IF_IDENTIFIER = 0
WHILE_IDENTIFIER = 0
WHILE_CURRENT = []

VAR_SZ = 8
COMMENT = '#'



def variable_id(name, funcname, depth):
    return name + "-" + funcname + "-" + str(depth)


def get_variable_object_via_json(element, funcname: str, depth: int) -> Variable:

    if element["action"] == "varget":
        return get_variable_object(element["name"], funcname, depth)
    
    print(element)
    if element["action"] == "rlop":
        
        if element["op"] == "*x":

            # asm.add([
            # ])
            evaluate_expression(element["value"], funcname, depth)
            asm.add([
                f"{COMMENT} using evaluating address inside",

            ])

            # print(VARIABLES, funcname, depth)
            pointed_obj = get_variable_object_via_json(element["value"], funcname, depth)
            # print(pointed_obj)
            return Variable(f"*{pointed_obj.varname}", pointed_obj.funcname, pointed_obj.depth, pointed_obj.offset, pointed_obj.vartype, pointed_obj.globl, pointed_obj.unreference + 1)
        # return 

    # CAREFUL HERE, VALUEGET COULD COME FROM SOMETHING ELSE, DONT KNOW WHAT THOUGH
    if element["action"] == "valueget":
        return get_variable_object_via_json(element["value"], funcname, depth)
    
    if element["action"] == "arrayget":
        pass
        



# def get_variable_location_via_json(element, funcname: str, depth: int):

#     if element["action"] == "varget":
#         return get_variable_location(element["name"], funcname, depth)


def get_variable_object(varname: str, funcname: str, depth: int) -> Variable:

    global VARIABLES
    depth_iterator = depth

    while depth_iterator >= 0:
        var_id = variable_id(varname, funcname, depth_iterator)
        if var_id in VARIABLES[depth_iterator]:
            return VARIABLES[depth_iterator][var_id]
        if varname in VARIABLES[depth_iterator]:
            return VARIABLES[depth_iterator][varname]
        depth_iterator -= 1
        
    raise Exception(f"Undefined Variable {var_id}/{varname}")


def get_variable_location(varname: str, funcname: str, depth: int):

    obj = get_variable_object(varname, funcname, depth)

    if obj.globl:
        return f"{obj.varname}(%rip)"
    else:
        return f"{obj.offset}(%rbp)"


def get_variable(varname: str, funcname: str, depth: int):

    location = get_variable_location(varname, funcname, depth)
    push_location(location, f"push variable {varname}")



def push_location(location: str, comment: str = "Default comment, variable expr :')"):

    asm.add([
        f"{COMMENT} {comment}",
        f"push {location}",
        ""
    ])


def push_pointer(location: str, comment: str = "Default comment, pushing pointer :')"):

    asm.add([
        f"{COMMENT} {comment}",
        f"lea {location}, %rax",
        "push %rax",
        ""
    ])

def push_unreference(location: str, unref_count: int, comment: str = "Default comment, pushing unreferenced variable :')"):

    asm.add([
        f"{COMMENT} {comment} unref_count: {unref_count}",
        f"mov {location}, %rax",
        ["mov (%rax), %rbx",
        "mov %rbx, %rax"] * unref_count,
        "push %rax",
        ""
    ])



def end_function_here():
    asm.add([
        "mov %rbp, %rsp",
        "pop %rbp",
        "ret",
        ""
    ])


def evaluate_scope(body, funcname, return_type, depth):

    # print("++++", body)

    global VARIABLES, VARIABLE_OFFSET, LOOP_IDENTIFIER, IF_IDENTIFIER, WHILE_IDENTIFIER, WHILE_CURRENT

    if isinstance(body, dict):

        if "action" in body and body["action"] == "scope":
            # VARIABLES.append({})
            evaluate_scope(body["body"], funcname, return_type, depth)
            # VARIABLES.pop()
            return
        
        # VARIABLES.append({})
        evaluate_scope([body], funcname, return_type, depth)
        # VARIABLES.pop()
        return
    

    for element in body:
        
        if element["action"] == "return":
            
            if len(element["value"].keys()) != 0:
                evaluate_expression(element["value"], funcname, depth)
                asm.add([
                    f"{COMMENT} returning value",
                    f"pop %rax",
                    ""
                ])
            
            end_function_here()
            continue

        if element["action"] == "expr":
            evaluate_expression(element["value"], funcname, depth)
            continue

        if element["action"] == "vardef":

            varname = element['name']
            vartype = element['type']
            varsize = math.prod(element["size"])

            var_id = variable_id(varname, funcname, depth)
            
            memory_var_size = VAR_SZ * varsize
            
            asm.add([
                f"{COMMENT} space for var {var_id}, type {vartype}",
                f"sub ${memory_var_size}, %rsp",
                ""
            ])

            VARIABLE_OFFSET += memory_var_size
            # VARIABLES[depth][var_id] = (var_id, -VARIABLE_OFFSET, vartype)
            VARIABLES[depth][var_id] = Variable(varname, funcname, depth, -VARIABLE_OFFSET, vartype)

            if len(element["value"].keys()) > 0:
                # should be changed so that int c = 3; covers also global variables.
                rebuild_varset = {'action': 'varset', 'left_value': {'action': 'varget', 'name': varname}, 'op': '=', 'value': element['value']}
                evaluate_scope([rebuild_varset], funcname, return_type, depth)

            continue

        if element["action"] == "varset":

            keep_one_bit_flag = False

            evaluate_expression(element['value'], funcname, depth)

            left_val = element["left_value"]
            if left_val["action"] == "rlop" and left_val["op"] == "*x":
                evaluate_expression(left_val["value"], funcname, depth, True)
            
            elif left_val["action"] == "varget" and "name" in left_val:
                
                var_obj = get_variable_object(left_val["name"], funcname, depth)
                location = var_obj.location()
                keep_one_bit_flag = (var_obj.vartype == "bool")

                asm.add([
                    f"{COMMENT} varset, pushing address",
                    f"lea {location}, %rax",
                    "push %rax",
                    ""
                ])  

            else:
                print("HUGH", left_val)    

            

            asm.add([
                f"{COMMENT} dereference element",
                f"pop %rax {COMMENT} get back where to put",
                f"pop %rbx {COMMENT} get back evaluated value",
                ""
            ])

            if keep_one_bit_flag:
                asm.add(f"and $1, %rbx")

            asm.add([
                f"mov %rbx, (%rax)", 
                ""
            ])




            
            # var_obj = get_variable_object_via_json(element["left_value"], funcname, depth)
            # location = var_obj.location()
            # vartype = var_obj.vartype
            # # vartype = get_variable_location_via_json(element["left_value"], funcname, depth)
            
            # asm.add([
            #     f"{COMMENT} varset left_value, for type {vartype}",
            #     f"pop %rax"
            # ])

            # asm.add([
            #     f"mov %rax, {location}",
            #     ""
            # ])
            continue

        if element["action"] == "for":

            asm.add([
                f"{COMMENT} Starting loop", 
                ""
            ])

            VARIABLES.append({})
            # print(element["init"])
            evaluate_scope([element["init"]], funcname, return_type, depth + 1)
            
            LOOP_IDENTIFIER += 1
            starting_point = f"start_loop_{LOOP_IDENTIFIER}"
            end_point = f"end_loop_{LOOP_IDENTIFIER}"

            asm.add(f"{starting_point}:", indent=False)

            # basic condition
            asm.add(f"{COMMENT} checking condition")
            evaluate_expression(element["condition"], funcname, depth + 1)

            asm.add([
                "pop %rax",
                "test %rax, %rax",
                f"jz {end_point}",
                ""
            ])

            scope = element["body"]
            # body = scope["body"]
            evaluate_scope(scope, funcname, return_type, depth + 1)

            evaluate_scope([element["update"]], funcname, return_type, depth + 1)

            # jump point
            asm.add([
                f"{COMMENT} back to start",
                f"jmp {starting_point}",
                ""
            ])

            asm.add(f"{end_point}:", indent=False)
            asm.add("")

            VARIABLES.pop()
            continue

        if element["action"] == "if":

            IF_IDENTIFIER += 1
            VARIABLES.append({})

            if_point = f"if_point_{IF_IDENTIFIER}"
            if_past = f"if_past_{IF_IDENTIFIER}"
            
            evaluate_expression(element["condition"], funcname, depth + 1)


            asm.add([
                f"{COMMENT} checking if condition",
                "pop %rax",
                "test %rax, %rax",
                f"jnz {if_point}",
                f"jmp {if_past}",
                ""
            ])

            asm.add(f"{if_point}:", indent=False)

            scope_if = element["body"]
            # scope_if = 
            evaluate_scope(scope_if, funcname, return_type, depth)
            
            asm.add([
                f"jmp {if_past}",
                ""
            ])
            asm.add(f"{if_past}:", indent=False)
            VARIABLES.pop()
            continue

        if element["action"] == "ifelse":

            IF_IDENTIFIER += 1
            VARIABLES.append({})

            if_point = f"if_point_{IF_IDENTIFIER}"
            if_else_point = f"if_else_{IF_IDENTIFIER}"
            if_past = f"if_past_{IF_IDENTIFIER}"
            
            evaluate_expression(element["condition"], funcname, depth + 1)


            asm.add([
                f"{COMMENT} checking ifelse condition",
                "pop %rax",
                "test %rax, %rax",
                f"jnz {if_point}",
                f"jmp {if_else_point}",
                ""
            ])

            asm.add(f"{if_point}:", indent=False)

            scope_if = element["body_if"]
            evaluate_scope(scope_if, funcname, return_type, depth)
            asm.add(f"jmp {if_past}")

            asm.add(f"{if_else_point}:", indent=False)

            scope_if = element["body_else"]
            evaluate_scope(scope_if, funcname, return_type, depth)
            asm.add(f"jmp {if_past}")

            asm.add(f"{if_past}:", indent=False)
            continue


        if element["action"] == "while":

            VARIABLES.append({})

            WHILE_IDENTIFIER += 1
            WHILE_CURRENT.append(WHILE_IDENTIFIER)

            while_entry = f"while_entry_{WHILE_IDENTIFIER}"
            while_out = f"while_out_{WHILE_IDENTIFIER}"

            asm.add([
                f"{COMMENT} while loop",
                ""
            ])

            asm.add(f"{while_entry}:", indent=False)

            evaluate_expression(element["condition"], funcname, depth + 1)
            asm.add([
                f"{COMMENT} checking while condition",
                "pop %rax",
                "test %rax, %rax",
                f"jz {while_out}",
                ""
            ])

            # print(element["body"])
            evaluate_scope(element["body"], funcname, return_type, depth + 1)
            
            asm.add([
                f"{COMMENT} starting loop again",
                f"jmp {while_entry}",
                ""
            ])

            asm.add(f"{while_out}:", indent=False)

            WHILE_CURRENT.pop()
            VARIABLES.pop()
            continue

        if element["action"] == "scope":

            VARIABLES.append({})
            evaluate_scope(element["body"], funcname, return_type, depth + 1)
            VARIABLES.pop()


        if element["action"] == "keyword":

            if element["keyword"] == "continue":

                asm.add([
                    f"{COMMENT} continue keyword",
                    f"jmp while_entry_{WHILE_CURRENT[-1]}",
                    ""
                ])

            if element["keyword"] == "break":

                asm.add([
                    f"{COMMENT} break keyword",
                    f"jmp while_out_{WHILE_CURRENT[-1]}",
                    ""
                ])

        print(element)

        
def define_function(funcname, return_type, arguments, scope, added):

    global VARIABLES, VARIABLE_OFFSET

    
    current_depth = 1
    VARIABLES.append({})

    if added is not None:
        print(added)
        evaluate_scope(added, funcname, return_type, current_depth)
    
    VARIABLE_OFFSET = 0

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




def evaluate_expression(expr, funcname, depth: int, for_pointers: bool = False):

    boolean_cast_rax = "test %rax, %rax\n\tsetnz %al\n\tmovzx %al, %rax\n\t"
    boolean_cast_rbx = "test %rbx, %rbx\n\tsetnz %bl\n\tmovzx %bl, %rbx\n\t"

    operators = {
        "+": "add %rax, %rbx",
        "-": "sub %rbx, %rax\n\tmov %rax, %rbx",
        "*": "imul %rax, %rbx",
        "/": "cqo\n\tidivq %rbx\n\tmov %rax, %rbx",
        "%": "xor %rdx, %rdx\n\tidivq %rbx\n\tmov %rdx, %rbx",
        "&&": f"{boolean_cast_rax}{boolean_cast_rbx}and %rax, %rbx",
        "||": f"{boolean_cast_rax}{boolean_cast_rbx}or %rax, %rbx",
        "&": "and %rax, %rbx",
        "|": "or %rax, %rbx",
        "<": "cmp %rbx, %rax\n\tsetl %bl\n\tmovzx %bl, %rbx",
        ">": "cmp %rax, %rbx\n\tsetl %bl\n\tmovzx %bl, %rbx",
        "<=": "cmp %rbx, %rax\n\tsetle %bl\n\tmovzx %bl, %rbx",
        ">=": "cmp %rax, %rbx\n\tsetle %bl\n\tmovzx %bl, %rbx",
        "==": "cmp %rax, %rbx\n\tsete %bl\n\tmovzx %bl, %rbx",
    }

    unioperators = {
        "!": f"{boolean_cast_rax}{boolean_cast_rbx}and $1, %rax"
    }

    # print(expr)
            # print(left_val)
    if expr["action"] == "lrop":

        if expr["op"] == "&x":
            left_val = expr["left_value"]
            var_obj = get_variable_object_via_json(left_val, funcname, depth)
            location = var_obj.location()
            push_pointer(location, "pushing pointer from expr")
            return
    
    if expr["action"] == "rlop":

        if expr["op"] == "*x":

            evaluate_expression(expr["value"], funcname, depth)
            
            asm.add([
                f"{COMMENT} dereferencing variable",
                "pop %rbx",
                "mov (%rbx), %rax",
                "push %rax",
                ""
            ])
            return



    if expr["action"] == "var":
        get_variable(expr["name"], funcname, depth)
        return
    
    if expr["action"] == "valueget":
        evaluate_expression(expr["value"], funcname, depth)
        return

        value = expr["value"]
        if value["action"] == "rlop" and value["op"] == "*x":
            pass

        var_obj = get_variable_object_via_json(expr["value"], funcname, depth)
        location = var_obj.location()
        
        if var_obj.unreference == 0:
            push_location(location, "pushing var through valueget")
        else:
            push_unreference(location, var_obj.unreference, "pushing unreferenced pointer")

        # location = get_variable_location_via_json(expr["value"], funcname, depth)
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

        # print("----", expr)
        if "value" in expr:
            evaluate_expression(expr['value'], funcname, depth)
            return

        var = get_variable_object(expr["name"], funcname, depth)
        push_location(var.location(), "HEEEEEEEEELP")
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
        return

    if expr["action"] == "uniop":
        
        evaluate_expression(expr["value"], funcname, depth)
        current_uniop = expr["uniop"]

        asm.add([
            f"{COMMENT} uniop {current_uniop}",
            "pop %rax",
            unioperators[current_uniop],
            "push %rax",
            ""
        ])

    print(expr)

        



        




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
            # var_id = variable_id(, 'main', 0)
            VARIABLES[0][element['name']] = Variable(element['name'], 'main', 0, 0, element['type'], True, 0)
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
        # print(asm.own_asm)



