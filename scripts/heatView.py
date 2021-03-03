# -*- coding: utf-8 -*-
import matplotlib as mpl
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from numpy import linspace
import sys
from matplotlib import gridspec

import numpy as np

# %matplotlib inline

#temperatures = [73.41,73.71,73.69,73.39,73.72,74.04,74.03,73.69,73.69,74.04,74.01,73.66,73.36,73.68,73.67,73.34,72.05,72.36,72.35,72.04,72.37,72.70,72.69,72.35,72.34,72.70,72.67,72.32,72.01,72.33,72.32,71.99,70.12,70.44,70.43,70.11,70.45,70.80,70.78,70.43,70.42,70.79,70.77,70.41,70.08,70.42,70.40,70.07,67.63,67.96,67.95,67.62,67.97,68.34,68.33,67.96,67.94,68.33,68.32,67.93,67.59,67.94,67.93,67.58,64.59,64.94,64.94,64.58,64.96,65.35,65.34,64.94,64.93,65.34,65.34,64.92,64.56,64.93,64.91,64.55,61.03,61.41,61.40,61.03,61.42,61.85,61.84,61.40,61.40,61.84,61.84,61.39,61.00,61.39,61.39,61.00,56.98,57.39,57.39,56.98,57.40,57.87,57.86,57.38,57.38,57.86,57.86,57.38,56.97,57.38,57.38,56.96,52.48,52.92,52.92,52.49,52.93,53.43,53.43,52.91,52.91,53.43,53.42,52.91,52.48,52.92,52.91,52.47]
temperatures = [0] * 128

def parse_tfile(tfilename, index, orig_line):
    position=index
    line=orig_line.rstrip()
    line=line.split('\t')
    i = 0
    for value in line[position:]:
        temperatures[i] = float(value)
        i+=1

def parse_tfile_header(tfilename, orig_line):
    position=0
    line=orig_line.split('\t')
    while (line[position].startswith('LC')):
        position+=1
    return position


def plot_opaque_cube(ax, x=10, y=20, z=30, dx=40, dy=50, dz=60, color='cyan'):

    kwargs = {'alpha': 1, 'color': color}

    xx = np.linspace(x, x+dx, 2)
    yy = np.linspace(y, y+dy, 2)
    zz = np.linspace(z, z+dz, 2)

    xx, yy = np.meshgrid(xx, yy)

    ax.plot_surface(xx, yy, z, **kwargs)
    ax.plot_surface(xx, yy, z+dz, **kwargs)

    yy, zz = np.meshgrid(yy, zz)
    ax.plot_surface(x, yy, zz, **kwargs)
    ax.plot_surface(x+dx, yy, zz, **kwargs)

    xx, zz = np.meshgrid(xx, zz)
    ax.plot_surface(xx, y, zz, **kwargs)
    ax.plot_surface(xx, y+dy, zz, **kwargs)
    # ax.set_xlim3d(-dx, dx*2, 20)
    # ax.set_xlim3d(-dx, dx*2, 20)
    # ax.set_xlim3d(-dx, dx*2, 20)
    #plt.title("Cube")
    #plt.show()




if __name__ == "__main__":
    color_lvl = 200
    color=cm.RdYlBu(linspace(1.0, 0.0, color_lvl+1))
    tfilename = str(sys.argv[1])
    pngFolder = str(sys.argv[2])
    try:
        samplingRate = int(sys.argv[3])
    except:
        samplingRate = 1
    fp = open(tfilename, 'r')
    lines = fp.readlines()
    index = parse_tfile_header(tfilename, lines[0])
    count = 0
    for line in lines[1:]:
        if (count%samplingRate != 0):
            count+=1
            continue

        fig = plt.figure()
        gs = gridspec.GridSpec(1, 2, width_ratios=[4, 1]) 
        ax = fig.add_subplot(gs[0], projection='3d')
        parse_tfile(tfilename, index, line)
        tmin = 65.0
        tmax = 81.0
        #tmin = min(temperatures)
        #tmax = max(temperatures)
        temp_range = tmax - tmin
        quantum = temp_range / color_lvl
        count+=1
        for zz in range(8):
            for xx in range(4):
                for yy in range(4):
                    ind = yy + 4*xx + 4*4*zz
                    offset = temperatures[ind] - tmin
                    offset = int(offset/quantum)
                    if offset < 0:
                        offset = 0
                    if offset > color_lvl:
                        offset = color_lvl
                    plot_opaque_cube(ax, 0+xx, 0+yy-0.2*zz, 0+zz, 1, 1, 0.2, color[offset])

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
        plt.title('Time step: '+str(count)+' ms')
        plt.annotate("8 layer, 4x4 HMC stack", xy=(0.1, 0.8), xycoords='figure fraction')
        plt.annotate("Top layer", xy=(0.08, 0.7), xycoords='figure fraction')
        plt.annotate("Bottom layer", xy=(0.08, 0.2), xycoords='figure fraction')
        #ax.view_init(210,70)   #reversed
        ax.view_init(10,20)
        plt.axis('off')


        ##Adding the bottom layer view
        ax = fig.add_subplot(gs[1])
        b_temp = np.random.random(( 4 , 4 )) 
        index=0
        for i in range(4):
            for j in range(4):
                b_temp[i][j] = temperatures[index]
                index+=1
        cmap = mpl.cm.RdYlBu_r
        norm = mpl.colors.Normalize(vmin=tmin, vmax=tmax)
        plt.imshow( b_temp , cmap = cmap , norm=norm, interpolation = 'nearest' ) 
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
        plt.annotate("Bottom layer\ncross section", xy=(0.73, 0.65), xycoords='figure fraction')





        ##Adding colorbar
        #add_axes(left,bottom,width,height)
        ax1 = fig.add_axes([0.92, 0.30, 0.03, 0.35])
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
        cb1.set_label('Temperature (in deg C)')

    

        if samplingRate == 1:
            fileNum = count
        else:
            fileNum = int(count/samplingRate)+1
        plt.savefig(pngFolder + '/heatmap_'+str(fileNum)+'.png', bbox_inches='tight')
        #plt.show()
        #exit()
        plt.close(fig)

    fp.close()
