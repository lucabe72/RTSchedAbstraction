import sys
from clang.cindex import Index, CursorKind

def extract_structure(input_file, struct_name):
    index = Index.create()
    tu = index.parse(input_file, args=['-DCONFIG_SMP'])

    for cursor in tu.cursor.walk_preorder():
        if cursor.kind == CursorKind.STRUCT_DECL and cursor.spelling == struct_name:
            if cursor.is_definition():
                start = cursor.extent.start.line
                end = cursor.extent.end.line

                with open(input_file, 'r') as f:
                    lines = f.readlines()

                return ''.join(lines[start - 1:end])
    return None

def main():
    if len(sys.argv) != 4:
        print("Usage: python " + sys.argv[0] + " <struct name> <input file> <output file>")
        return

    struct_name, input_file, output_file = sys.argv[1], sys.argv[2], sys.argv[3]
    structure = extract_structure(input_file, struct_name)

    if structure:
        with open(output_file, 'w') as out:
            out.write(structure)
        print(f"struct '{struct_name}' extracted to '{output_file}'")
    else:
        print(f"Struct '{struct_name}' not found in {input_file}")

if __name__ == "__main__":
    main()
