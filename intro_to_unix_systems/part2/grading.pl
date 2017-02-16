# grading.pl
# Matthew Rundle
# cse20198.01

# filename is taken as command line argument
$filename = @ARGV[0];

# open file
open(FILE,$filename);
@lines = <FILE>;

# Create the hash
%student_hash = ();

$line_number = 0;

foreach(@lines) {

	if($line_number == 0){
		@catagories_array = split(',',$_);
	}else{
		my @student_array = split(',',$_);
		my $student_name = $student_array[0];
		shift @student_array;
		$student_hash{$student_name} = $_;
	}

	$line_number++;
}

# Pop off the "names" part
shift @catagories_array;

@ass_type;	#assignment type
@ass_weight; #assignment weight

$homework_tot = 0;
$quiz_tot = 0;
$exam1_tot = 0;
$exam2_tot = 0;

foreach(@catagories_array){
	@temp = split('-',$_);
	push (@ass_type, $temp[0]);
	push (@ass_weight, $temp[1]);

	if($temp[0] =~ m/Homework/){
		$homework_tot += $temp[1];
	}
	elsif($temp[0] =~ m/Quiz/){
		$quiz_tot += $temp[1];
	}
	elsif($temp[0] =~ m/Exam 1/){
		$exam1_tot += $temp[1];
	}
	elsif($temp[0] =~ m/Exam 2/){
		$exam2_tot += $temp[1];
	}else{}
}

open (GRADES, '>FinalGrades.tex');

#########################################################################
#             DOCUMENT MARKUP BEGINNING                                 #
#########################################################################
print GRADES "\\documentclass{article}\n";
print GRADES "\\usepackage{listings}\n\n";

print GRADES "\\usepackage{float}\n";
print GRADES "\\restylefloat{table}\n\n";

print GRADES "\\title{Final Grades (via Perl)}\n";
print GRADES "\\author{Matthew Rundle}\n\n";

print GRADES "\\begin{document}\n";
print GRADES "\\maketitle\n\n";

print GRADES "\\begin{table}[H]\n";
print GRADES "\\centering\n";
print GRADES "\\begin{tabular}{ | c | c | c | c | c | c | } \\hline\n";
print GRADES "Student Name & Homework & Quiz & Exam 1 & Exam 2 & Final Grade \\\\ \\hline\n";
#########################################################################
#             DOCUMENT MARKUP ENDING                                    #
#########################################################################

 #Go through each key and calculate the stuff
foreach my $key (sort  {$a cmp $b} keys %student_hash) {

	@student_array = split(',',$student_hash{$key});
	shift @student_array;

	$student_hw_grade = 0;
	$student_quiz_grade = 0;
	$student_exam1_grade = 0;
	$student_exam2_grade = 0;

	$array_iterator = 0;

	foreach(@student_array){
		if($ass_type[$array_iterator] =~ m/Homework/){
			$student_hw_grade += $student_array[$array_iterator];
		}
		elsif($ass_type[$array_iterator] =~ m/Quiz/){
			$student_quiz_grade += $student_array[$array_iterator];
		}
		elsif($ass_type[$array_iterator] =~ m/Exam 1/){
			$student_exam1_grade += $student_array[$array_iterator];
		}
		elsif($ass_type[$array_iterator] =~ m/Exam 2/){
			$student_exam2_grade += $student_array[$array_iterator];
		}else{}

		$array_iterator++;
	}

	my $student_hw_pct = int((($student_hw_grade / $homework_tot)*100)+0.5);
	my $student_quiz_pct = int((($student_quiz_grade / $quiz_tot)*100)+0.5);
	my $student_exam1_pct = int((($student_exam1_grade / $exam1_tot)*100)+0.5);
	my $student_exam2_pct = int((($student_exam2_grade / $exam2_tot)*100)+0.5);

	my $student_final_grade_pct = int(($student_hw_pct*0.5)+($student_quiz_pct*0.1)+($student_exam1_pct*0.2)+($student_exam2_pct*0.2)+0.5);
	my $student_final_grade;

	if($student_final_grade_pct >= 94){ $student_final_grade = 'A'}
	elsif($student_final_grade_pct >= 90){ $student_final_grade = 'A-'}
	elsif($student_final_grade_pct >= 88){ $student_final_grade = 'B+'}
	elsif($student_final_grade_pct >= 84){ $student_final_grade = 'B'}
	elsif($student_final_grade_pct >= 80){ $student_final_grade = 'B-'}
	elsif($student_final_grade_pct >= 78){ $student_final_grade = 'C+'}
	elsif($student_final_grade_pct >= 74){ $student_final_grade = 'C'}
	elsif($student_final_grade_pct >= 70){ $student_final_grade = 'C-'}
	elsif($student_final_grade_pct >= 60){ $student_final_grade = 'D'}
	else{ $student_final_grade = 'F'}

	
	#########################################################################
	#             DOCUMENT MARKUP BEGINNING                                 #
	#########################################################################
	print GRADES "$key & $student_hw_pct\\% & $student_quiz_pct\\% & $student_exam1_pct\\% & $student_exam2_pct\\% & $student_final_grade \\\\ \\hline\n";
	#########################################################################
	#             DOCUMENT MARKUP ENDING                                    #
	#########################################################################

}

#########################################################################
#             DOCUMENT MARKUP BEGINNING                                 #
#########################################################################
print GRADES "\\end{tabular}\n";
print GRADES "\\end{table}\n";
print GRADES "\\end{document}\n";
#########################################################################
#             DOCUMENT MARKUP ENDING                                    #
#########################################################################

`latex FinalGrades.tex`;
`dvips FinalGrades.dvi`;
`ps2pdf FinalGrades.ps`;

