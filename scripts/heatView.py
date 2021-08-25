#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import matplotlib as mpl
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d import art3d
from matplotlib import cm
from numpy import linspace
import sys
import math
import getopt
from matplotlib import gridspec
import shutil, os
from matplotlib.patches import Rectangle

import numpy as np


def usage():
  print ('Generate video from temperature trace')
  print ('Usage:')
  print ('  %s  -t <tracefile> -o <output directory> -s <sampling rate>  ' % sys.argv[0])
  print ('''Detailed options: \n
     --cores_in_x: Number of cores in x dimension (default 2)
     --cores_in_y: Number of cores in y dimension (default 2)
     --cores_in_z: Number of cores in z dimension (default 1)
     --banks_in_x: Number of memory banks in x dimension (default 4)
     --banks_in_y: Number of memory banks in y dimension (default 4)
     --banks_in_z: Number of memory banks in z dimension (default 8)
     --arch_type: Architecture type = 3D, 3Dmem, 2.5D, DDR (default 3Dmem)
     --plot_type: Generated view = 3D or 2D (default 3D)
     --layer_to_view: Layer number to view in 3D plot (starting from 0) (default 0)
     --type_to_view: Layer type to view in 3D plot (CORE or MEMORY) (default MEMORY)
     --verbose (or -v): Enable verbose output
     --inverted_view (or -i): Enable inverted view (heat sink on bottom)
     --debug: Enable debug priting
     --tmin: Minimum temperature to use for scale (default 65 deg C)
     --tmax: Maximum temperature to use for scale (default 81 deg C)
     --samplingRate (or -s): Sampling rate, specify an integer (default 1)
     --traceFile (or -t): Input trace file (no default value)
     --output (or -o): output directory (default maps)
     --clean (or -c): Clean if directory exists
  ''')
  sys.exit(2)
        

cores_in_x=2
cores_in_y=2
cores_in_z=1

banks_in_x=4
banks_in_y=4
banks_in_z=8

arch_type="3Dmem"        ##option = 3D, other.
inverted_view=False

plot_type="3D"          ##option = 2D, 3D
MAX_ROWS_2D_PLOT=3

#for 3D plot
layer_to_view=0
type_to_view="MEMORY"          #CORE, MEMORY


debug=False
verbose= False

tfilename = 'temperature.trace'
pngFolder = 'maps'
samplingRate = 1
tmin = 65.0
tmax = 81.0
cleanDir=False


if not sys.argv[1:]:
  usage()

opts_passthrough = [ 'cores_in_x=', 'cores_in_y=', 'cores_in_z=', 'banks_in_x=', 'banks_in_y=', 'banks_in_z=', 'arch_type=', 'plot_type=', 'layer_to_view=', 'type_to_view=', 'verbose', 'inverted_view', 'debug', 'tmin=', 'tmax=', 'samplingRate=', 'traceFile=', 'output=', 'clean' ]

try:
  #                     arguments,  shortopts,  longopts
  opts, args = getopt.getopt(sys.argv[1:], "hvidcs:t:o:", opts_passthrough)

except: #getopt.GetoptError, e:
  # print help information and exit:
  print (e)
  usage()
for o, a in opts:
  if o == '-h':
    usage()
  if o == '-v' or o == '--verbose':
    verbose = True
  if o == '-d' or o == '--debug':
    debug = True
  if o == '-i' or o == '--inverted_view':
    inverted_view = True
  if o == '--cores_in_x':
    cores_in_x = int(a)
  if o == '--cores_in_y':
    cores_in_y = int(a)
  if o == '--cores_in_z':
    cores_in_z = int(a)
  if o == '--banks_in_x':
    banks_in_x = int(a)
  if o == '--banks_in_y':
    banks_in_y = int(a)
  if o == '--banks_in_z':
    banks_in_z = int(a)
  if o == '--arch_type':
    arch_type = a
  if o == '--plot_type':
    plot_type = a
  if o == '--layer_to_view':
    layer_to_view = int(a)
  if o == '--type_to_view':
    type_to_view = a
  if o == '-s' or o == '--samplingRate':
    samplingRate = int(a)
  if o == '-t' or o == '--traceFile':
    tfilename = a
  if o == '-o' or o == '--output':
    pngFolder = a
  if o == '--tmin':
    tmin = float(a)
  if o == '--tmax':
    tmax = float(a)
  if o == '-c' or o == '--clean':
    cleanDir = True

if (debug):
    print ("Command line options:")
    print (opts)

if (arch_type == "DDR"):
    plot_type = "2D"




# %matplotlib inline

#temperatures = [73.41,73.71,73.69,73.39,73.72,74.04,74.03,73.69,73.69,74.04,74.01,73.66,73.36,73.68,73.67,73.34,72.05,72.36,72.35,72.04,72.37,72.70,72.69,72.35,72.34,72.70,72.67,72.32,72.01,72.33,72.32,71.99,70.12,70.44,70.43,70.11,70.45,70.80,70.78,70.43,70.42,70.79,70.77,70.41,70.08,70.42,70.40,70.07,67.63,67.96,67.95,67.62,67.97,68.34,68.33,67.96,67.94,68.33,68.32,67.93,67.59,67.94,67.93,67.58,64.59,64.94,64.94,64.58,64.96,65.35,65.34,64.94,64.93,65.34,65.34,64.92,64.56,64.93,64.91,64.55,61.03,61.41,61.40,61.03,61.42,61.85,61.84,61.40,61.40,61.84,61.84,61.39,61.00,61.39,61.39,61.00,56.98,57.39,57.39,56.98,57.40,57.87,57.86,57.38,57.38,57.86,57.86,57.38,56.97,57.38,57.38,56.96,52.48,52.92,52.92,52.49,52.93,53.43,53.43,52.91,52.91,53.43,53.42,52.91,52.48,52.92,52.91,52.47]
total_cores = cores_in_x*cores_in_y*cores_in_z
total_banks = banks_in_x*banks_in_y*banks_in_z

temperatures_core = [0] * total_cores
temperatures_bank = [0] * total_banks

def parse_tfile(tfilename, orig_line):
    line=orig_line.rstrip()
    line=line.split('\t')
    i = 0
    if (debug):
        print ("DEBUG::Temperature trace:\n%s" %line)
    for value in line[0:total_cores]:
        temperatures_core[i] = float(value)
        i+=1
    i = 0
    for value in line[total_cores:]:
        temperatures_bank[i] = float(value)
        i+=1

def parse_tfile_header(tfilename, orig_line):
    count_core_column=0
    count_bank_column=0
    column=0
    line=orig_line.split('\t')
    if (debug):
        print ("DEBUG::Temperature trace file header:\n%s" %line)

    while (line[column].startswith('C')):
        count_core_column+=1
        column+=1
    while (line[column].startswith('B')):
        count_bank_column+=1
        column+=1
    if (count_core_column!=total_cores):
        print("WARNING: Total core columns does not match the number of cores!!")
        print("    Number cores:%d, number columns:%d" %(total_cores, count_core_column))
    if (count_bank_column!=total_banks):
        print("WARNING: Total bank columns does not match the number of banks!!")
        print("    Number banks:%d, number columns:%d" %(total_banks, count_bank_column))


def plot_opaque_cube(ax, x=10, y=20, z=30, dx=40, dy=50, dz=60, color='cyan', alpha=1):

    if (debug):
        print("DEBUG:: plot_opaque_cube: x=%d,y=%d,z=%d" %(x,y,z))

    kwargs = {'alpha': alpha, 'color': color, 'edgecolor': 'k', 'shade':False}

    xx = np.linspace(x, x+dx, 2)
    yy = np.linspace(y, y+dy, 2)
    zz = np.linspace(z, z+dz, 2)

    xxx, yyy = np.meshgrid(xx, yy)
    zzz = z*np.ones(4).reshape(2, 2)
    ax.plot_surface(xxx, yyy, zzz,    **kwargs)
    ax.plot_surface(xxx, yyy, zzz+dz, **kwargs)

    yyy, zzz = np.meshgrid(yy, zz)
    xxx = x*np.ones(4).reshape(2, 2)
    ax.plot_surface(xxx,    yyy, zzz, **kwargs)
    ax.plot_surface(xxx+dx, yyy, zzz, **kwargs)

    xxx, zzz = np.meshgrid(xx, zz)
    yyy = y*np.ones(4).reshape(2, 2)
    ax.plot_surface(xxx, yyy,    zzz, **kwargs)
    ax.plot_surface(xxx, yyy+dy, zzz, **kwargs)

    # ax.set_xlim3d(-dx, dx*2, 20)
    # ax.set_xlim3d(-dx, dx*2, 20)
    # ax.set_xlim3d(-dx, dx*2, 20)
    #plt.title("Cube")
    #plt.show()

def plot_3D_structure(ax, tmin, tmax, xdim, ydim, zdim, zstart, xwidth, ywidth, temperatures, title_message, axes_postprocess=True, inverted=False, layer_type="Core", adjust=0):
    if (debug):
        print ("DEBUG:: plot_3D_structure: xwidth = %f" %xwidth)
    color_lvl = 200
    shift_amount = 0  #earlier 0.2
    color=cm.RdYlBu_r(linspace(0.0, 1.0, color_lvl+1))
    temp_range = tmax - tmin
    quantum = temp_range / color_lvl
    ind=0
    if (inverted):
        zrange = reversed(range(zdim))
    else:
        zrange = range(zdim)
    for zz in zrange:
        for xx in range(xdim):
            for yy in range(ydim):
                offset = temperatures[ind] - tmin
                offset = int(offset/quantum)
                if offset < 0:
                    offset = 0
                if offset > color_lvl:
                    offset = color_lvl
                plot_opaque_cube(ax, 0+xwidth*xx, 0+ywidth*yy-shift_amount*(zz+zstart), 0+zz+zstart, xwidth, ywidth, 0.2, color[offset], 1)
                ind += 1
        if (inverted):
            layer_num = zdim-zz-1
        else:
            layer_num = zz
        annotate_text = layer_type + " L"+ str(layer_num)
        if (zdim > 1 or zstart > 0):
            ax.text(xx+3,-1.2+adjust,zz+zstart+1.0,annotate_text,(0,1,0), verticalalignment='center', fontsize=17)
#        ax.annotate("Time step = "+str(count) +" ms", xy=(xx+1, 0), xycoords='axes points', fontsize=21)

    if (axes_postprocess==True):        #true only for the last plot in 3D.
        yint = []
        locs, labels = plt.yticks()
        for each in locs:
            yint.append(int(each))
        plt.yticks(yint)
    
        yint = []
        locs, labels = plt.xticks()
        for each in locs:
            yint.append(int(each))
        plt.xticks(yint)
        plt.title(title_message, y=-0.01, fontsize=21)
        if (xdim > ydim):
            ax.set_ylim(0, xdim)
        elif (ydim > xdim):
            ax.set_xlim(0, ydim)

        ##ax.view_init(210,70)   #reversed
        if (zdim+zstart < 5):
            ax.set_zlim3d(bottom=0.0, top=5)
        ax.view_init(10,20)     #elevation, azimuthal
        plt.axis('off')
        #plt.show()
                


def plot_2D_map(ax, tmin, tmax, xdim, ydim, xwidth, ywidth, title_message, temperatures):
    if (debug):
        print("DEBUG:: plot_2D_map: xdim=%d,ydim=%d,temperatures=%s" %(xdim,ydim,temperatures))

    cmap = mpl.cm.RdYlBu_r
    norm = mpl.colors.Normalize(vmin=tmin, vmax=tmax)
    arr = np.array(temperatures)
    arr1 = arr.reshape(xdim, ydim)
    #plt.imshow( arr1 , cmap = cmap , norm=norm, interpolation = 'nearest', aspect='equal', origin='upper') 
    plt.pcolormesh( arr1, cmap = cmap, norm=norm, edgecolor='k') 
    #plt.grid(color='k', linewidth=2)
    plt.axis('off')
    plt.title(title_message, fontsize=21)
    ax.set_aspect('equal')
    ax.invert_yaxis()




##main function. Script begins from here
if __name__ == "__main__":
        #    parse_args()

    print("\n")
    print("Received temperature filename: %s" %tfilename)
    print("Received output directory name: %s" %pngFolder)
    print("Setting sampling rate: %d" %samplingRate)
    print("Setting min. temperature limit (blue color): %.1f" %tmin)
    print("Setting max. temperature limit (red color) : %.1f" %tmax)
    print("\n")
    if not os.path.exists(pngFolder):
        os.mkdir(pngFolder)
    elif (cleanDir):
        shutil.rmtree(pngFolder)
        os.mkdir(pngFolder)
    fp = open(tfilename, 'r')
    lines = fp.readlines()
    parse_tfile_header(tfilename, lines[0])         #pass first line to process
    count = 0                   #count of line number
    for line in lines[1:]:
        if (count%samplingRate != 0):
            count+=1
            continue
        fig = plt.figure(figsize=(14, 8))

        if (plot_type == "2D"):
            max_banks = max(banks_in_z, cores_in_z)
            rows = min(MAX_ROWS_2D_PLOT, max_banks)
            cols_banks = int(math.ceil(float(banks_in_z)/rows))
            cols_cores = int(math.ceil(float(cores_in_z)/rows))

            gs = gridspec.GridSpec(nrows=rows, ncols=cols_cores+cols_banks) 
        elif (arch_type == "3D"):
            gs = gridspec.GridSpec(nrows=1, ncols=2, width_ratios=[3, 1]) 
        else:
            gs = gridspec.GridSpec(nrows=1, ncols=3, width_ratios=[1, 1, 0.5]) 

        parse_tfile(tfilename, line)
        if (debug):
            print("\n")
            print("DEBUG::Core temperatures:", temperatures_core)
            print("DEBUG::Bank temperatures:", temperatures_bank)
        print("Processing line %d" %count)

        count+=1
        if (plot_type == "2D"):
            for j in range(cores_in_z):
                xindex = int(j%MAX_ROWS_2D_PLOT)
                yindex = int(j/MAX_ROWS_2D_PLOT)
                #print (xindex, yindex)
                ax = fig.add_subplot(gs[xindex, yindex])
                xdim = cores_in_x
                ydim = cores_in_y
                start_index = j * xdim * ydim
                end_index = start_index + xdim * ydim
                temperatures = temperatures_core[start_index : end_index]
                title_message = "CORE layer " + str(j)
                plot_2D_map(ax, tmin, tmax, xdim, ydim, 1, 1, title_message, temperatures)

            for j in range(banks_in_z):
                xindex = int(j%MAX_ROWS_2D_PLOT)
                yindex = cols_cores + int(j/MAX_ROWS_2D_PLOT)
                #print (xindex, yindex)
                ax = fig.add_subplot(gs[xindex, yindex])
                xdim = banks_in_x
                ydim = banks_in_y
                start_index = j * xdim * ydim
                end_index = start_index + xdim * ydim
                temperatures = temperatures_bank[start_index : end_index]
                title_message = "MEM. layer " + str(j)
                plot_2D_map(ax, tmin, tmax, xdim, ydim, 1, 1, title_message, temperatures)

        #beginning of 3D plotting
        else:
            ax = fig.add_subplot(gs[0], projection='3d')
                        #ind = yy + cores_in_y*xx + cores_in_x*cores_in_y*zz

            #core
            if (arch_type=="3D"):
                xwidth=(float)(banks_in_x)/cores_in_x
                ywidth=(float)(banks_in_y)/cores_in_y
                if (inverted_view):
                    zstart = 0
                else:
                    zstart = banks_in_z
                postprocess=False
                title_message = None
                adj=0.0   #adjust annotation
            else:
                xwidth=1
                ywidth=1
                zstart = 0
                postprocess=True
                title_message = "Core temperature map"
                adj=0
            plot_3D_structure(ax, tmin, tmax, cores_in_x, cores_in_y, cores_in_z, zstart, xwidth, ywidth, temperatures_core, title_message, postprocess, inverted_view, "Core ", adj)
            #ax_h, ax_w = 4, 4##
#            p = Rectangle((0,0),
#                           ax_h, ax_w,
#                           fc = 'none',
#                           color='red',
#                           linewidth=5,
#                           linestyle='dotted')
#            ax.add_patch(p)
#            art3d.pathpatch_2d_to_3d(p, z=0, zdir = "x")
            #plot_opaque_cube(ax, 0, 0, 0, cores_in_x, cores_in_y, cores_in_z, color='none', alpha=0.05)##

            #memory
            if (arch_type=="3D"):
                postprocess=True
                title_message = "3D architecture temperature map"
                if (inverted_view):
                    zstart = cores_in_z
                else:
                    zstart = 0
                adj=0.7   #adjust annotation
            else:
                postprocess=True
                if (arch_type == "2.5D"):
                    title_message = "Mem. temperature map"
                else:
                    title_message = "Off-chip mem. temp. map"
                ax = fig.add_subplot(gs[1], projection='3d')
                adj=0
            xwidth=1
            ywidth=1
            plot_3D_structure(ax, tmin, tmax, banks_in_x, banks_in_y, banks_in_z, zstart, xwidth, ywidth, temperatures_bank, title_message, postprocess, inverted_view, "Mem.", adj)

            #ax_h, ax_w = 4, 4 ##
            #ax_h, ax_w = ax.bbox.height, ax.bbox.width
            #ax_h = ax.bbox.transformed(fig.gca().transAxes).height
            #print (ax_h, ax_w)
            #p = Rectangle((0,0),
            #               ax_h, ax_w,
            #               fc = 'none',
            #               color='red',
            #               linewidth=5,
            #               linestyle='dotted')
            #ax.add_patch(p)
            #art3d.pathpatch_2d_to_3d(p, z=0, zdir = "x")
            #plot_opaque_cube(ax, 0, 0, 0, banks_in_x, banks_in_y, banks_in_z, color='none', alpha=0.05)##

            arch_string = "Arch. type: " + str(arch_type) + ", "
            arch_string += "Core: " + str(cores_in_x) + "x" + str(cores_in_y) + "x" + str(cores_in_z) + ", "
            arch_string += "Memory: "+ str(banks_in_x) + "x" + str(banks_in_y) + "x" + str(banks_in_z) 
            plt.annotate(arch_string, xy=(0.13, 0.93), xycoords='figure fraction', fontsize=21)
            plt.annotate("Time step = "+str(count) +" ms", xy=(0.13, 0.85), xycoords='figure fraction', fontsize=21)
            if (inverted_view):
                #plt.axhline(0.03, color='r')
                plt.annotate("Heat Sink at bottom", xy=(0.13, 0.15), xycoords='figure fraction', fontsize=21)
            else:
                #plt.axhline(0.85, color='r')
                plt.annotate("Heat Sink at top", xy=(0.13, 0.75), xycoords='figure fraction', fontsize=21)





##            ##Adding the bottom layer view
            
            if (arch_type=="3D"):
                ax = fig.add_subplot(gs[1])
            else:
                ax = fig.add_subplot(gs[2])


            if (type_to_view == "CORE"):
                if (layer_to_view >= cores_in_z):
                    print ("\nERROR:: INVALID layer_to_view parameter. Should be less than number of core layers\n")
                    exit()
                xdim = cores_in_x
                ydim = cores_in_y
                start_index = layer_to_view * xdim * ydim
                end_index = start_index + xdim * ydim
                temperatures = temperatures_core[start_index : end_index]
                title_message = "CORE layer " + str(layer_to_view)
            elif (type_to_view == "MEMORY"):
                if (layer_to_view >= banks_in_z):
                    print ("\nERROR:: INVALID layer_to_view parameter. Should be less than number of memory layers\n")
                    exit()
                xdim = banks_in_x
                ydim = banks_in_y
                start_index = layer_to_view * xdim * ydim
                end_index = start_index + xdim * ydim
                temperatures = temperatures_bank[start_index : end_index]
                title_message = "MEM. layer " + str(layer_to_view)
            else:
                print ("\nERROR:: INVALID type_to_view parameter. Should be CORE or MEMORY\n")
                exit()

            plot_2D_map(ax, tmin, tmax, xdim, ydim, 1, 1, title_message, temperatures)

        #plt.annotate("Core layer", xy=(0.08, 0.7), xycoords='figure fraction')
        #plt.annotate("Memory layer", xy=(0.08, 0.65), xycoords='figure fraction')
        #plt.annotate("Memory layer", xy=(0.08, 0.2), xycoords='figure fraction')




        ##Adding colorbar
        #add_axes(left,bottom,width,height)
        ax1 = fig.add_axes([0.92, 0.20, 0.03, 0.55])
        cmap = mpl.cm.RdYlBu_r
        norm = mpl.colors.Normalize(vmin=tmin, vmax=tmax)
        # ColorbarBase derives from ScalarMappable and puts a colorbar
        # in a specified axes, so it has everything needed for a
        # standalone colorbar.  There are many more kwargs, but the
        # following gives a basic continuous colorbar with ticks
        # and labels.
        cb1 = mpl.colorbar.ColorbarBase(ax1, cmap=cmap,
                                        norm=norm,
                                        orientation='vertical')
        cb1.set_label('Temperature (in deg C)', size=21)
        cb1.ax.tick_params(labelsize=18)

    

        if samplingRate == 1:
            fileNum = count
        else:
            fileNum = int(count/samplingRate)+1
        plt.savefig(pngFolder + '/heatmap_'+str(fileNum)+'.png', bbox_inches='tight')
        #plt.show()
        #exit()
        plt.close(fig)

    fp.close()

os.system("cd " + pngFolder)
image_files=pngFolder+"/heatmap_%d.png"
video_file=pngFolder+"/output.avi"
os.system("ffmpeg -framerate 1 -i " + image_files + " -start_number 1 -c:v mpeg4 -vtag xvid -qscale:v 4 -c:a libmp3lame -qscale:a 5 " + video_file)

##        b_temp = np.random.random(( 4 , 4 )) 
##        index=0
##        for i in range(4):
##            for j in range(4):
##                b_temp[i][j] = temperatures[index]
##                index+=1
##        cmap = mpl.cm.RdYlBu_r
##        norm = mpl.colors.Normalize(vmin=tmin, vmax=tmax)
##        #print(b_temp)
##        plt.imshow( b_temp , cmap = cmap , norm=norm, interpolation = 'nearest', aspect='equal', origin='lower') 
##        #yint = []
##        #locs, labels = plt.yticks()
##        #print(locs)
##        #for each in locs:
##        #    yint.append(int(each))
##        #plt.yticks(yint)
##        #print(yint)
##
##        #yint = []
##        #locs, labels = plt.xticks()
##        #print(locs)
##        #for each in locs:
##        #    yint.append(int(each))
##        #plt.xticks(yint)
##        #print(yint)
##        plt.yticks([0,1,2,3])
##        plt.xticks([0,1,2,3])
##        plt.annotate("Bottom layer\ncross section", xy=(0.73, 0.65), xycoords='figure fraction')
##
##

