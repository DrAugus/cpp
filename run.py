import os
import platform
import subprocess
import sys
import getopt
import argparse
import numpy

parser = argparse.ArgumentParser(
    description="INVOKE CMAKE OR EXECUTE APPOINT PROGRAM")
parser.add_argument('-type', default='Debug', help='cmake build type')
parser.add_argument('-target', help='appoint a file to compile')
parser.add_argument('-run', action='store_true', help='run some target')
parser.add_argument('-l', action='store_true', help='list all cpp')
parser.add_argument('-j', default=10, type=int,
                    help='make flags, default is 10')
args = parser.parse_args()

project_path = os.path.realpath(os.path.dirname(__file__))
print("project_path:", project_path)

path3rd = [
    project_path + '/3rd/fmt/'
]


def mkdir_build(path=""):
    if path == "":
        current_directory = os.getcwd()
    else:
        current_directory = path
    build_dir = os.path.join(current_directory, 'build')
    if not os.path.exists(build_dir):
        os.makedirs(build_dir)
    return build_dir


def build3rd(path):
    print("build3rd, path", path)
    build_dir = mkdir_build(path)
    print("build3rd, build_dir", build_dir)
    # https://fmt.dev/latest/usage.html
    if 'fmt' in path:
        os.chdir(build_dir)
        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + build_dir]
        subprocess.run(['cmake', path] + cmake_args,  check=True)
        # install
        subprocess.run(['make'],  check=True)


def cmake(build_type):

    for v in path3rd:
        build3rd(v)

    os.chdir(project_path)
    build_dir = mkdir_build()
    print("cmake, build_dir", build_dir)

    cmake_args = ['-DCMAKE_BUILD_TYPE=' + build_type]
    cmake_cfg = ['--config', build_type]

    print("\n\nconfig cmake\n")
    subprocess.run(['cmake', '-B', build_dir] + cmake_args,  check=True)
    print("\n\nbuild\n")
    subprocess.run(['cmake', '--build', build_dir] + cmake_cfg, check=True)


def cmake_appoint(target, j, build_type):
    print("cmake_appoint, target", target, "build_type", build_type)
    os.chdir(project_path)
    build_dir = mkdir_build()
    print("cmake_appoint, build_dir", build_dir)
    cmake_args = ['--build', build_dir, '--config',
                  build_type, '--target', target, '-j', str(j), '--']
    print("cmake_appoint, cmake_args", cmake_args)
    subprocess.run(['cmake'] + cmake_args,  check=True)


def find_file_path():
    src_path = project_path + '/src'
    l1 = os.listdir(src_path)
    # print(l1)
    all_cpp = []
    for i in range(0, len(l1)):
        l2 = os.path.join(src_path, l1[i])
        prefix = '/src/' + l1[i] + '/'
        file = os.listdir(l2)
        file = list(filter(lambda e: e.endswith('.cpp') or e.endswith('.c'), file))
        file = list(map(lambda e: prefix + e, file))
	# split cpp
        file = list(map(lambda e: e.split('.cpp')[0], file))
	# split c
        file = list(map(lambda e: e.split('.c')[0], file))
        all_cpp += file
        # print(file)
    # print("all_cpp", all_cpp)
    return all_cpp


def handle_l():
    len_l = len(all_cpp)
    print(len_l)
    list_index = [i*10 for i in range(int(len_l/10))]
    list_index.append(len_l)
    # print(list_index)
    for i in range(1, len(list_index)):
        new_l = all_cpp[list_index[i-1]:list_index[i]]
        for v in new_l:
            print(v)
        get_in = input("\nPress Enter to continue...\n> Tap 'q' to quit...\n")
        if get_in == 'q':
            break


if __name__ == '__main__':
    print("===================")
    print("======= run =======")
    print("===================\n\n")
    build_type = args.type
    all_cpp = find_file_path()
    # print(all_cpp)
    while 1:
        if args.l:
            handle_l()
            break

        if args.target:
            cmake_appoint(args.target, args.j, build_type)
            run_target = list(filter(lambda e: args.target in e, all_cpp))
            print("\n\nrun_target", run_target)
            print(">>>>>>>>>>")
            subprocess.run(['build'+run_target[0]],  check=True)
            break
        else:
            cmake(build_type)
            break
