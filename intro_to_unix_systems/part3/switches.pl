# switches.pl
# Matthew Rundle
# cse20198.01

# filename is taken as command line argument
$filename = @ARGV[0];

# open file
open(FILE,$filename);
@lines = <FILE>;

# if line has 7 components, NEW JACK
# otherwise, continuation of old jack

$line_number = 0;
@switch_names = ();
$current_machine;

foreach(@lines) {

	@lineArray = split(',',$_);
  #take the quotations out (globally on line)
	foreach(@lineArray){
		$_ =~ s/\"//g;
	}

	#get array size
	$arraySize = @lineArray;

	if($line_number == 0){
		@catagoryArray = @lineArray;
	}
	else{ 
		if(!(@lineArray[0] eq "")){        #switch - create a new hash for each switch, push name into array of switches
			#parse the name
			$machine_name = @lineArray[0]; 
			$switch_hash{$machine_name} = $_;
			# keep track of current machine
			$current_machine = $machine_name;
			# push name into array of machine names
			push (@switch_names,$machine_name)
			# now create new switch hash to push machines into
			%{"$machine_name"};
		}
		#now actually push the machine into the new hash
		${"$current_machine"}{@lineArray[3]} = $_;
	}

	$line_number++;
}

##################################################
open (MACHINES, '>switches.tex');

print MACHINES "\\documentclass{article}\n";
print MACHINES "\\usepackage{listings}\n\n";

print MACHINES "\\usepackage{float}\n";
print MACHINES "\\restylefloat{table}\n\n";

print MACHINES "\\title{Notre Dame Switches}\n";
print MACHINES "\\author{Matthew Rundle}\n\n";

print MACHINES "\\begin{document}\n";
print MACHINES "\\maketitle\n\n";
##################################################


# go through each hash (in switch array) and print elements - be sure
# to pop off the switch name of those with 6 elements instead of 5
foreach(@switch_names){

  ################################################
	print MACHINES "\\begin{table}[H]\n";
	print MACHINES "\\caption{$_} \\label{tab:title}\n";
	print MACHINES "\\centering\n";
	print MACHINES "\\begin{tabular}{ | c | c | c | c | c | } \\hline\n";
	print MACHINES "Jack & Room & Host & MAC & Switch Port \\\\ \\hline\n";
	##################################################

	foreach my $key (sort  {$a cmp $b} keys %{"$_"}){

		@machine_info = split(',',${"$_"}{$key});

		foreach(@machine_info){
			$_ =~ s/\"//g;
			$_ =~ s/ //g;
		}
	
		$Jack = @machine_info[1];
		$Room = @machine_info[2];
		$Host = @machine_info[3];
		$MAC = @machine_info[4];
		$SwitchPort = @machine_info[5];

		print MACHINES "$Jack & $Room & $Host & $MAC & $SwitchPort \\\\ \\hline\n";
	}

	print MACHINES "\\end{tabular}\n";
	print MACHINES "\\end{table}\n";
}

print MACHINES "\\end{document}\n";

`pdflatex switches.tex`
