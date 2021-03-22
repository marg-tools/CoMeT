import sys, os, time, getopt, subprocess, tempfile


abspath = lambda d: os.path.abspath(os.path.join(d))

HOME = abspath(os.path.dirname(__file__))

postfix = '_base.sniper-x86_64'

def name_to_exe(name):
  return name.split('_')[0]+postfix

name_to_dir = {
  'perlbench': '400.perlbench',
  'bzip2': '401.bzip2',
  'gcc': '403.gcc',
  'bwaves': '410.bwaves',
  'gamess': '416.gamess',
  'mcf': '429.mcf',
  'milc': '433.milc',
  'zeusmp': '434.zeusmp',
  'gromacs': '435.gromacs',
  'cactusADM': '436.cactusADM',
  'leslie3d': '437.leslie3d',
  'namd': '444.namd',
  'gobmk': '445.gobmk',
  'dealII': '447.dealII',
  'soplex': '450.soplex',
  'povray': '453.povray',
  'calculix': '454.calculix',
  'hmmer': '456.hmmer',
  'sjeng': '458.sjeng',
  'GemsFDTD': '459.GemsFDTD',
  'libquantum': '462.libquantum',
  'h264ref': '464.h264ref',
  'tonto': '465.tonto',
  'lbm': '470.lbm',
  'omnetpp': '471.omnetpp',
  'astar': '473.astar',
  'wrf': '481.wrf',
  'sphinx3': '482.sphinx3',
  'xalancbmk': '483.xalancbmk',
}

name_to_input_index = {
  'perlbench': {
    'test:': [],
    'train': [],
    'ref':   ['checkspam', 'diffmail', 'splitmail'],
  },
  'bzip2': {
    'test':  [],
    'train': [],
    'ref':   ['input.source', 'chicken.jpg', 'liberty.jpg', 'input.program', 'text.html', 'input.combined'],
  },
  'gcc': {
    'test':  [],
    'train': [],
    'ref':   ['166', '200', 'c_typeck', 'cp_decl', 'expr', 'expr2', 'g23', 's04', 'scilab'],
  },
  'bwaves': {
    'test':  [],
    'train': [],
    'ref':   ['name'],
  },
  'gamess': {
    'test':  [],
    'train': [],
    'ref':   ['cytosine.2', 'h2ocu2+.gradient', 'triazolium'],
  },
  'mcf': {
    'test':  [],
    'train': [],
    'ref':   ['inp'],
  },
  'milc': {
    'test':  [],
    'train': [],
    'ref':   ['su3imp'],
  },
  'zeusmp': {
    'test':  [],
    'train': [],
    'ref':   ['name'],
  },
  'gromacs': {
    'test':  [],
    'train': [],
    'ref':   ['gromacs'],
  },
  'cactusADM': {
    'test':  [],
    'train': [],
    'ref':   ['benchADM'],
  },
  'leslie3d': {
    'test':  [],
    'train': [],
    'ref':   ['leslie3d'],
  },
  'namd': {
    'test':  [],
    'train': [],
    'ref':   ['namd'],
  },
  'gobmk': {
    'test':  [],
    'train': [],
    'ref':   ['13x13', 'nngs', 'score2', 'trevorc', 'trevord'],
  },
  'dealII': {
    'test':  [],
    'train': [],
    'ref':   ['name'],
  },
  'soplex': {
    'test':  [],
    'train': [],
    'ref':   ['pds_50.mps', 'ref'],
  },
  'povray': {
    'test':  [],
    'train': [],
    'ref':   ['SPEC_benchmark_ref'],
  },
  'calculix': {
    'test':  [],
    'train': [],
    'ref':   ['hyperviscoplastic'],
  },
  'hmmer': {
    'test':  [],
    'train': [],
    'ref':   ['nph3', 'retro'],
  },
  'sjeng': {
    'test':  [],
    'train': [],
    'ref':   ['ref'],
  },
  'GemsFDTD': {
    'test':  [],
    'train': [],
    'ref':   ['ref'],
  },
  'libquantum': {
    'test':  [],
    'train': [],
    'ref':   ['ref'],
  },
  'h264ref': {
    'test':  [],
    'train': [],
    'ref':   ['foreman_ref_baseline_encodelog', 'foreman_ref_main_encodelog', 'sss_main_encodelog'],
  },
  'tonto': {
    'test':  [],
    'train': [],
    'ref':   ['tonto'],
  },
  'lbm': {
    'test':  [],
    'train': [],
    'ref':   ['name'],
  },
  'omnetpp': {
    'test':  [],
    'train': [],
    'ref':   ['omnetpp'],
  },
  'astar': {
    'test':  [],
    'train': [],
    'ref':   ['BigLakes2048', 'rivers'],
  },
  'wrf': {
    'test':  [],
    'train': [],
    'ref':   ['wrf'],
  },
  'sphinx3': {
    'test':  [],
    'train': [],
    'ref':   ['an4'],
  },
  'xalancbmk': {
    'test':  [],
    'train': [],
    'ref':   ['ref'],
  },
}

inputmap = {
  'test': 'test',
  'train': 'train',
  'ref': 'ref',
  # small is not valid
  'large': 'train',
  'huge': 'ref',
}

def allbenchmarks():
  return map(lambda x: x[0], sorted(name_to_dir.iteritems(), key=lambda x: x[1]))

def allinputs():
  return inputmap.keys()



class Program:

  def __init__(self, program, nthreads, inputsize, benchmark_options = []):
    origprogram = program
    if '_' in program:
      pgm = program.split('_', 1)
      program = pgm[0]
      origindex = pgm[1]
      index = origindex
      # First try to use the index as a number
      try:
        index = int(index)
      except ValueError, e:
        # Convert index name to index number
        if program in name_to_input_index:
          inps = name_to_input_index[program]
          if inputsize in inps:
            idxs = inps[inputsize]
            if index in idxs:
              #print 'finding index', idxs, index
              index = idxs.index(index)
    else:
      index = 0
    if program not in allbenchmarks():
      raise ValueError("Invalid benchmark %s" % program)
    if inputsize not in allinputs():
      raise ValueError("Invalid input size %s" % inputsize)
    # Index of 0 always works (at least one run)
    if index != 0 and index >= len(name_to_input_index[program][inputsize]):
      raise ValueError("Invalid program index (%s/%s)" % (origprogram, index))
    self.program = program
    self.nthreads = nthreads
    self.inputsize = inputmap[inputsize]
    self.index = index


  def ncores(self):
    return self.nthreads


  def run(self, graphitecmd, postcmd = ''):
    rc = 1 # Indicate failure if there are any problems
    origcwd = os.getcwd()
    rundir = None
    try:
      # Make the new directories, and cd there
      rundir = tempfile.mkdtemp()
      os.chdir(rundir)
      # Link in all of the binaries and data files
      for datadir in (os.path.join('data','all','input'), os.path.join('data',self.inputsize,'input'), 'exe', 'Spec'):
        datadir = os.path.abspath(os.path.join(HOME,'CPU2006',name_to_dir[self.program],datadir))
        if not os.path.exists(datadir):
          continue
        for filename in os.listdir(datadir):
          filename = os.path.abspath(os.path.join(datadir, filename))
          os.symlink(filename, os.path.join(rundir,os.path.basename(filename)))
      # Additional preparation for some benchmarks
      if self.program == 'wrf':
	for datadir in (os.path.join('data','all','input','le','32'),):
	  datadir = os.path.abspath(os.path.join(HOME,'CPU2006',name_to_dir[self.program],datadir))
	  if not os.path.exists(datadir):
	    raise Exception('Unable to find wrf-specific files')
	  for filename in os.listdir(datadir):
	    filename = os.path.abspath(os.path.join(datadir, filename))
	    os.symlink(filename, os.path.join(rundir,os.path.basename(filename)))
      elif self.program == 'sphinx3':
	for datadir in (os.path.join('data',self.inputsize,'input'),):
	  datadir = os.path.abspath(os.path.join(HOME,'CPU2006',name_to_dir[self.program],datadir))
	  if not os.path.exists(datadir):
	    raise Exception('Unable to find sphinx3-specific files')
          files = []
	  for filename in os.listdir(datadir):
            if '.le.raw' in filename:
              files.append(filename.split('.le.raw')[0])
              destfilename = filename.split('.le.raw')[0]+'.raw'
	      filename = os.path.abspath(os.path.join(datadir, filename))
	      os.symlink(filename, os.path.join(rundir,os.path.basename(destfilename)))
          ctlfp = open(os.path.join(rundir,'ctlfile'), 'w')
          for f in sorted(files):
            ctlfp.write('%s %u\n' % (f, os.stat(os.path.join(rundir,f+'.raw')).st_size))
          ctlfp.close()
      input_filenames = []
      for indir in ('all', self.inputsize):
        try:
          input_filenames += os.listdir(os.path.join(HOME,'CPU2006',name_to_dir[self.program],'data',indir,'input'))
        except OSError:
          pass
      omp_cmd = '%s/run_spec.pl --name %s --exe %s --size %s --index %s ' % (HOME, self.program, name_to_exe(self.program), self.inputsize, self.index) + ' '.join(map(lambda x: '--input %s' % x, sorted(input_filenames)))
      cmd_to_run = subprocess.Popen(omp_cmd, shell=True, stdout=subprocess.PIPE).communicate()[0].split(' ',1)
      cmd_to_run = ' '.join([os.path.join(rundir,cmd_to_run[0]),len(cmd_to_run) == 2 and cmd_to_run[1] or ''])
    except Exception, e:
      print 'Error: ' + str(e) + ' in %s' % __file__
      os.chdir(origcwd)
      if rundir != None:
        os.system('rm -rf "%s"' % rundir)
      raise

    rc = run_bm(self.program, cmd_to_run, graphitecmd, env = '', postcmd = postcmd)
    os.chdir(origcwd)
    os.system('rm -rf "%s"' % rundir)
    return rc


  def rungraphiteoptions(self):
    return ''


def run(cmd):
  sys.stdout.flush()
  sys.stderr.flush()
  rc = os.system(cmd)
  rc >>= 8
  return rc

def run_bm(bm, cmd, submit, env, postcmd = ''):
  print '[CPU2006]', '[========== Running benchmark', bm, '==========]'
  cmd = env + ' ' + submit + ' ' + cmd + ' ' + postcmd
  print '[CPU2006]', 'Running \'' + cmd + '\':'
  print '[CPU2006]', '[---------- Beginning of output ----------]'
  rc = run(cmd)
  print '[CPU2006]', '[----------    End of output    ----------]'
  print '[CPU2006]', 'Done.'
  return rc
