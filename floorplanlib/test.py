from collections import namedtuple
import filecmp
import os
import shutil
import subprocess


FloorplanTestConfig = namedtuple('FloorplanTestConfig', ['name', 'commandline_args'])


def check_result(test_name):
    errors = []

    expected_dir = os.path.join('test/expected', test_name)
    actual_dir = os.path.abspath(os.path.join('test/actual', test_name))

    for filename in os.listdir(expected_dir):
        expected_filename = os.path.join(expected_dir, filename)
        actual_filename = os.path.join(actual_dir, filename)

        if not os.path.exists(actual_filename):
            errors.append(f'file not created: {filename}')
        else:
            with open(expected_filename) as f:
                expected_content = f.read()
            with open(actual_filename) as f:
                actual_content = f.read()
            
            expected_content = expected_content.format(actual_dir=actual_dir)

            if actual_content != expected_content:
                description = 'different nb of lines'
                for nb, (l1, l2) in enumerate(zip(actual_content.splitlines(), expected_content.splitlines())):
                    if l1 != l2:
                        description = f'first differing line is {nb}:\n   actual:   {l1.strip()}\n   expected: {l2.strip()}'
                        break
                errors.append(f'file content differs: {filename}: {description}')

    return errors


def run(test):
    actual = os.path.join('test/actual', test.name)
    expected = os.path.join('test/expected', test.name)
    args = test.commandline_args + ['--out', actual]

    if os.path.exists(actual):
        shutil.rmtree(actual)

    try:
        result = subprocess.check_call(['python3', 'create.py'] + args)
    except subprocess.CalledProcessError:
        print(f'{test.name}: ERROR (call failed)')
        return

    # check output
    errors = check_result(test.name)

    if errors:
        print(f'{test.name}: ERROR')
        for error in errors:
            for line in error.splitlines():
                print(f'   {line}')
    else:
        print(f'{test.name:<35s}: ok')


def main():
    TESTS = [
        FloorplanTestConfig(
            name='2d',
            commandline_args=[
                '--mode', 'DDR',
                '--cores', '4x4', '--corex', '1mm', '--corey', '1mm',
                '--banks', '8x8', '--bankx', '0.9mm', '--banky', '0.9mm',
            ]
        ),
        FloorplanTestConfig(
            name='2d_different_thicknesses',
            commandline_args=[
                '--mode', 'DDR',
                '--cores', '4x4', '--corex', '1mm', '--corey', '1mm', '--core_thickness', '70um',
                '--banks', '8x8', '--bankx', '0.9mm', '--banky', '0.9mm', '--bank_thickness', '60um',
                '--tim_thickness', '10um',
            ]
        ),
        FloorplanTestConfig(
            name='3d_offchip',
            commandline_args=[
                '--mode', '3Dmem',
                '--cores', '4x4', '--corex', '1mm', '--corey', '1mm',
                '--banks', '8x8x2', '--bankx', '0.9mm', '--banky', '0.9mm',
            ]
        ),
        FloorplanTestConfig(
            name='2.5d_bigger_mem',
            commandline_args=[
                '--mode', '2.5D',
                '--cores', '4x4', '--corex', '1mm', '--corey', '1mm',
                '--banks', '8x8x2', '--bankx', '0.9mm', '--banky', '0.9mm',
                '--core_mem_distance', '7mm',
            ]
        ),
        FloorplanTestConfig(
            name='2.5d_bigger_core',
            commandline_args=[
                '--mode', '2.5D',
                '--cores', '4x4', '--corex', '1.8mm', '--corey', '1.8mm',
                '--banks', '8x8x2', '--bankx', '0.6mm', '--banky', '0.6mm',
                '--core_mem_distance', '7mm',
            ]
        ),
        FloorplanTestConfig(
            name='2.5d_core_mem_same_size',
            commandline_args=[
                '--mode', '2.5D',
                '--cores', '4x4', '--corex', '1.8mm', '--corey', '1.8mm',
                '--banks', '8x8x2', '--bankx', '0.9mm', '--banky', '0.9mm',
                '--core_mem_distance', '7mm',
            ]
        ),
        FloorplanTestConfig(
            name='3d',
            commandline_args=[
                '--mode', '3D',
                '--cores', '4x4', '--corex', '0.9mm', '--corey', '0.9mm',
                '--banks', '8x8x4', '--bankx', '0.45mm', '--banky', '0.45mm',
                '--tim_thickness', '10um',
            ]
        ),
    ]

    seen_names = set()
    for test in TESTS:
        assert test.name not in seen_names
        seen_names.add(test.name)
        run(test)


if __name__ == '__main__':
    main()
