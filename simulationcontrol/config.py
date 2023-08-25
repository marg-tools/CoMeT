import os

HERE = os.path.dirname(os.path.abspath(__file__))
SNIPER = os.path.dirname(HERE)

RESULTS_FOLDER = os.path.join(SNIPER, 'results')
# make sure to change the floorplans accordingly when changing number of cores and memory banks
NUMBER_CORES_X = 2
NUMBER_CORES_Y = 2
NUMBER_CORES_Z = 1
NUMBER_MEM_BANKS_X = 4
NUMBER_MEM_BANKS_Y = 4
NUMBER_MEM_BANKS_Z = 8
SNIPER_CONFIG = 'gainestown_3D'

NUMBER_CORES = NUMBER_CORES_X * NUMBER_CORES_Y * NUMBER_CORES_Z


# video configuration
ARCH_TYPE = '3D'  # 3D, 3Dmem, 2.5D, or DDR
VIDEO_PLOT_3D = True
VIDEO_BREAKOUT_LAYER = 0
VIDEO_BREAKOUT_TYPE = 'CORE'  # CORE or MEMORY
VIDEO_INVERTED_VIEW = False  # inverted = heatsink on bottom
VIDEO_EXPLICIT_TMIN = None  # if None use default min and max values
VIDEO_EXPLICIT_TMAX = None  # if None use default min and max values
