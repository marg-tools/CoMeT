#!/usr/bin/perl

use warnings;
use Getopt::Long;
use IO::File;
#use Data::Dumper;

package Info;

sub new {
        my $class = shift;
	my $self = {};
        $self->{'input_files_base'} = [];
	bless $self, $class;
	return $self;
}

sub set_name {
	my $self = shift;
	$self->{'name'} = shift;
}

sub name {
	my $self = shift;
	return $self->{'name'};
}

sub set_exe_file {
	my $self = shift;
	$self->{'exe_file'} = shift;
}

sub exe_file {
	my $self = shift;
	return $self->{'exe_file'};
}

sub add_input_file {
	my $self = shift;
	push(@{$self->{'input_files_base'}}, shift);
	#print "Input file = ", @{$self->{'input_files_base'}}, "\n";
}

sub input_files_base {
	my $self = shift;
	return @{$self->{'input_files_base'}};
}

sub set_size {
	my $self = shift;
	$self->{'size'} = shift;
}

sub size {
	my $self = shift;
	return $self->{'size'};
}

package main;

# From SPEC/bin/util_common.pl
sub read_file {
    my($name) = @_;
    my (@temp);
    my $fh = new IO::File "<$name";
    # IO::File will close the file when $fh goes out of scope
    return () if !defined $fh;
    return <$fh>;
}

package Main;

# Import the SPEC perl module
my $filename = "object.pm";
open(PERLFILE, "<$filename");

# Slurp the file into a variable
my $holdTerminator = $/;
undef $/;
my $file = <PERLFILE>;
$/ = $holdTerminator;

# Evaulate the module
eval($file);

# Create a new object to pass into the invoke() function
my $info = new Info;
my $idx = 0;

Getopt::Long::GetOptions ('name=s'  => sub { shift; my $opt = shift; $info->set_name($opt); },
                          'exe=s'   => sub { shift; my $opt = shift; $info->set_exe_file($opt) } ,
                          'input=s' => sub { shift; my $opt = shift; $info->add_input_file($opt) },
                          'size=s'  => sub { shift; my $opt = shift; $info->set_size($opt) },
                          'index=i' => \$idx,
                         );

# Call invoke to determine the program name and parameters to use to call the program
#print STDERR Data::Dumper::Dumper($info);
my @arr = invoke($info);
#print STDERR Data::Dumper::Dumper(@arr);

if ($idx >= scalar(@arr)) {
	print STDERR "Invalid index\n";
	exit (1);
}

#print STDERR "\n INDEX = ${idx}\n";

if (!defined($arr[$idx]->{'command'})) {
	print STDERR "Undefined command!\n";
	exit(1);
}

# Create a new list that contains the required arguments
my @command = ();

push @command, ($arr[$idx]->{'command'});
my $args = $arr[$idx]->{'args'};
for (my $i = 0 ; $i <= $#$args; $i++) {
	push @command, $args->[$i];
}
if (defined($arr[$idx]->{'input'})) {
	push @command, "<";
	push @command, $arr[$idx]->{'input'};
}

# Print the command to run

print shift @command;
foreach my $cmd (@command) {
	print " $cmd";
}

exit(0);
