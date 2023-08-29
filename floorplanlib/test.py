from collections import namedtuple
import filecmp
import os
import shutil
import subprocess
import sys


FloorplanTestConfig = namedtuple('FloorplanTestConfig', ['name', 'commandline_args'])


def check_result(test_name):
    errors = []

    expected_dir = os.path.join('test/expected', test_name)
    actual_dir = os.path.abspath(os.path.join('test/actual', test_name))

    for filename in sorted(os.listdir(expected_dir)):
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
                        description = f'first differing line is {nb+1}:\n   actual:   {l1.strip()}\n   expected: {l2.strip()}'
                        break
                errors.append(f'file content differs: {filename}: {description}')

    return errors


def run(test, expect_fail=False):
    actual = os.path.join('test/actual', test.name)
    expected = os.path.join('test/expected', test.name)
    args = test.commandline_args + ['--out', actual]

    if os.path.exists(actual):
        shutil.rmtree(actual)

    print(f'{test.name:<35s}: ', end='')
    try:
        output = subprocess.check_output(['python3', 'create.py'] + args, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as e:
        if expect_fail:
            print(f'ok')
            return True
        else:
            print(f'ERROR (call failed)')
            for line in e.output.decode('utf-8').splitlines():
                print(f'   {line}')
            return False

    if expect_fail:
        print(f'ERROR (call expected to fail but did not fail)')
        return False

    # check output
    errors = check_result(test.name)

    if errors:
        print(f'ERROR')
        for error in errors:
            for line in error.splitlines():
                print(f'   {line}')
        return False
    else:
        print(f'ok')
        return True


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
            ]
        ),
        FloorplanTestConfig(
            name='2d_subcore',
            commandline_args=[
                '--mode', 'DDR',
                '--cores', '2x2', '--corex', '1mm', '--corey', '1mm', '--subcore-template', 'test/files/subcore_1mm.flp',
                '--banks', '8x8', '--bankx', '0.9mm', '--banky', '0.9mm',
            ]
        ),
        FloorplanTestConfig(
            name='3d_offchip_subcore',
            commandline_args=[
                '--mode', '3Dmem',
                '--cores', '2x2', '--corex', '1mm', '--corey', '1mm', '--subcore-template', 'test/files/subcore_1mm.flp',
                '--banks', '8x8x2', '--bankx', '0.9mm', '--banky', '0.9mm',
            ]
        ),
        FloorplanTestConfig(
            name='2.5d_bigger_mem_subcore',
            commandline_args=[
                '--mode', '2.5D',
                '--cores', '2x2', '--corex', '1mm', '--corey', '1mm', '--subcore-template', 'test/files/subcore_1mm.flp',
                '--banks', '2x2x2', '--bankx', '2mm', '--banky', '2mm',
                '--core_mem_distance', '2mm',
            ]
        ),
        FloorplanTestConfig(
            name='3d_subcore',
            commandline_args=[
                '--mode', '3D',
                '--cores', '2x2', '--corex', '1mm', '--corey', '1mm', '--subcore-template', 'test/files/subcore_1mm.flp',
                '--banks', '2x2x1', '--bankx', '1mm', '--banky', '1mm',
            ]
        ),
        # L3 tests
        FloorplanTestConfig(
            name='2d_l3_non-stacked',
            commandline_args=[
                '--mode', 'DDR',
                '--cores', '4x4', '--corex', '1mm', '--corey', '1mm',
                '--banks', '8x8', '--bankx', '0.9mm', '--banky', '0.9mm',
                '--cache_L3', 'non-stacked', '--cachex', '1mm', '--cachey', '4mm',
            ]
        ),
        FloorplanTestConfig(
            name='2d_l3_stacked',
            commandline_args=[
                '--mode', 'DDR',
                '--cores', '4x4', '--corex', '1mm', '--corey', '1mm',
                '--banks', '8x8', '--bankx', '0.9mm', '--banky', '0.9mm',
                '--cache_L3', 'stacked', '--cachex', '4mm', '--cachey', '4mm',
            ]
        ),
        FloorplanTestConfig(
            name='3d_offchip_l3_stacked',
            commandline_args=[
                '--mode', '3Dmem',
                '--cores', '4x4', '--corex', '1mm', '--corey', '1mm',
                '--banks', '8x8x2', '--bankx', '0.9mm', '--banky', '0.9mm',
                '--cache_L3', 'stacked', '--cachex', '4mm', '--cachey', '4mm',
            ]
        ),
        FloorplanTestConfig(
            name='3d_offchip_l3_non-stacked',
            commandline_args=[
                '--mode', '3Dmem',
                '--cores', '4x4', '--corex', '1mm', '--corey', '1mm',
                '--banks', '8x8x2', '--bankx', '0.9mm', '--banky', '0.9mm',
                '--cache_L3', 'non-stacked', '--cachex', '1mm', '--cachey', '4mm',
            ]
        ),
        FloorplanTestConfig(
            name='2.5d_core_l3_stacked',
            commandline_args=[
                '--mode', '2.5D',
                '--cores', '4x4', '--corex', '1.8mm', '--corey', '1.8mm',
                '--banks', '8x8x2', '--bankx', '0.9mm', '--banky', '0.9mm',
                '--core_mem_distance', '7mm',
                '--cache_L3', 'stacked', '--cachex', '6.4mm', '--cachey', '6.4mm',
            ]
        ),
        FloorplanTestConfig(
            name='2.5d_core_l3_non-stacked',
            commandline_args=[
                '--mode', '2.5D',
                '--cores', '4x4', '--corex', '1.8mm', '--corey', '1.8mm',
                '--banks', '8x8x2', '--bankx', '0.9mm', '--banky', '0.9mm',
                '--core_mem_distance', '7mm',
                '--cache_L3', 'non-stacked', '--cachex', '1.8mm', '--cachey', '6.4mm',
            ]
        ),
        FloorplanTestConfig(
            name='3d_l3_stacked',
            commandline_args=[
                '--mode', '3D',
                '--cores', '4x4', '--corex', '0.9mm', '--corey', '0.9mm',
                '--banks', '8x8x4', '--bankx', '0.45mm', '--banky', '0.45mm',
                '--cache_L3', 'stacked', '--cachex', '3.6mm', '--cachey', '3.6mm'
            ]
        ),
        FloorplanTestConfig(
            name='3d_l3_non-stacked',
            commandline_args=[
                '--mode', '3D',
                '--cores', '4x4', '--corex', '0.45mm', '--corey', '0.9mm',
                '--banks', '8x8x4', '--bankx', '0.45mm', '--banky', '0.45mm',
                '--cache_L3', 'non-stacked', '--cachex', '1.8mm', '--cachey', '3.6mm'
            ]
        ),
    ]

    EXPECT_TO_FAIL_TESTS = [
        FloorplanTestConfig(
            name='2d_subcore_floorplan_does_not_exist',
            commandline_args=[
                '--mode', 'DDR',
                '--cores', '2x2', '--corex', '1mm', '--corey', '1mm', '--subcore-template', 'test/files/doesnotexist.flp',
                '--banks', '8x8', '--bankx', '0.9mm', '--banky', '0.9mm',
            ]
        ),
        FloorplanTestConfig(
            name='2d_subcore_wrong_size',
            commandline_args=[
                '--mode', 'DDR',
                '--cores', '2x2', '--corex', '1mm', '--corey', '1mm', '--subcore-template', 'test/files/subcore_2mm.flp',
                '--banks', '8x8', '--bankx', '0.9mm', '--banky', '0.9mm',
            ]
        ),
    ]

    fails = 0
    total = 0
    seen_names = set()
    for test in TESTS:
        assert test.name not in seen_names
        seen_names.add(test.name)
        if not run(test):
            fails += 1
        total += 1

    for test in EXPECT_TO_FAIL_TESTS:
        assert test.name not in seen_names
        seen_names.add(test.name)
        if not run(test, expect_fail=True):
            fails += 1
        total += 1

    print('-'*50)
    if fails == 0:
        print(f'all {total} tests ok')
    else:
        print(f'{fails}/{total} tests failed')
        sys.exit(1)


if __name__ == '__main__':
    main()
