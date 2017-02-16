#! /use/bin/python -tt
import sys # import the system module 
import os

def main():

 FILE = sys.argv[1]
 student = dict()

 lineNumber = 0;
 for line in open(FILE, 'r'):
  if lineNumber == 0:
   catagoryList = line.split(',')
  else:
   studentList = line.split(',')
   student[studentList[0]] = line
  lineNumber = lineNumber + 1

 # Pop off the "names" part
 catagoryList.pop(0)

 ass_type = []	#assignment type
 ass_weight = [] #assignment weight

 homework_tot = float(0)
 quiz_tot = float(0)
 exam1_tot = float(0)
 exam2_tot = float(0)

 for line in catagoryList:
  temp = line.split('-')
  ass_type.append(temp[0])
  ass_weight.append(temp[1])
  if "Homework" in temp[0]:
   homework_tot += int(temp[1])
  elif "Quiz" in temp[0]:
   quiz_tot += int(temp[1])
  elif "Exam 1" in temp[0]:
   exam1_tot += int(temp[1])
  elif "Exam 2" in temp[0] :
   exam2_tot += int(temp[1])
  else:
   pass

 #print 'Homework: ' + str(homework_tot) + '\nQuiz: ' + str(quiz_tot) + '\nExam 1: ' + str(exam1_tot) + '\nExam 2: ' + str(exam2_tot) + '\n'

 ########################
 #  OPEN DAT FILE YO    #
 ########################
 FILE = open('FinalGrades.tex','w')
 #########################################################################
 #             DOCUMENT MARKUP BEGINNING                                 #
 #########################################################################
 FILE.write('\\documentclass{article}\n')
 FILE.write('\\usepackage{listings}\n\n') 

 FILE.write('\\usepackage{float}\n')
 FILE.write('\\restylefloat{table}\n\n')

 FILE.write('\\title{Final Grades (via Python)}\n')
 FILE.write('\\author{Matthew Rundle}\n\n')

 FILE.write('\\begin{document}\n')
 FILE.write('\\maketitle\n\n')

 FILE.write('\\begin{table}[H]\n')
 FILE.write('\\centering\n')
 FILE.write('\\begin{tabular}{ | c | c | c | c | c | c | } \\hline\n')
 FILE.write('Student Name & Homework & Quiz & Exam 1 & Exam 2 & Final Grade \\\\ \\hline\n')
 #########################################################################
 #             DOCUMENT MARKUP ENDING                                    #
 #########################################################################

 #Go through each key and calculate the stuff
 keylist = student.keys()
 keylist.sort()

 for key in keylist: #student.keys():
 
  student_array = student[key].split(',');
  student_array.pop(0)

  student_hw_grade = float(0)
  student_quiz_grade = float(0)
  student_exam1_grade = float(0)
  student_exam2_grade = float(0)

  array_iterator = 0

  for element in student_array:
   if("Homework" in ass_type[array_iterator]):
    student_hw_grade += int(student_array[array_iterator])
   elif("Quiz" in ass_type[array_iterator]):
    student_quiz_grade += int(student_array[array_iterator])
   elif("Exam 1" in ass_type[array_iterator]):
    student_exam1_grade += int(student_array[array_iterator])
   elif("Exam 2" in ass_type[array_iterator]):
    student_exam2_grade += int(student_array[array_iterator])
   else:
    pass
   array_iterator = array_iterator + 1

  student_hw_pct = int(((student_hw_grade / homework_tot)*100)+0.5)
  student_quiz_pct = int(((student_quiz_grade / quiz_tot)*100)+0.5)
  student_exam1_pct = int(((student_exam1_grade / exam1_tot)*100)+0.5)
  student_exam2_pct = int(((student_exam2_grade / exam2_tot)*100)+0.5)

  print key

  student_final_grade_pct = int((student_hw_pct*0.5)+(student_quiz_pct*0.1)+(student_exam1_pct*0.2)+(student_exam2_pct*0.2)+0.5)
  student_final_grade = 'ERROR'

  if(student_final_grade_pct >= 94):
   student_final_grade = 'A'
  elif(student_final_grade_pct >= 90):
   student_final_grade = 'A-'
  elif(student_final_grade_pct >= 88):
   student_final_grade = 'B+'
  elif(student_final_grade_pct >= 84):
   student_final_grade = 'B'
  elif(student_final_grade_pct >= 80):
   student_final_grade = 'B-'
  elif(student_final_grade_pct >= 78):
   student_final_grade = 'C+'
  elif(student_final_grade_pct >= 74):
   student_final_grade = 'C'
  elif(student_final_grade_pct >= 70):
   student_final_grade = 'C-'
  elif(student_final_grade_pct >= 60):
   student_final_grade = 'D'
  else:
   student_final_grade = 'F'

  #print key + " & " + str(student_hw_pct) + "\\% & " + str(student_quiz_pct) + "\\% & " + str(student_exam1_pct) + "\\% & " + str(student_exam2_pct) + "\\% & " + str(student_final_grade) + "\\\\ \\hline\n"

  #########################################################################
  #             DOCUMENT MARKUP BEGINNING                                 #
  #########################################################################
  printString = key + ' & ' + str(student_hw_pct) + '\\% & ' + str(student_quiz_pct) + '\\% & ' + str(student_exam1_pct) + '\\% & '+ str(student_exam2_pct) + '\\% & ' + str(student_final_grade) + '\\\\ \\hline\n'
  FILE.write(printString)
  #########################################################################
  #             DOCUMENT MARKUP ENDING                                    #
  #########################################################################

 #########################################################################
 #             DOCUMENT MARKUP BEGINNING                                 #
 #########################################################################
 FILE.write('\\end{tabular}\n')
 FILE.write('\\end{table}\n')
 FILE.write('\\end{document}\n')
 #########################################################################
 #             DOCUMENT MARKUP ENDING                                    #
 #########################################################################

 ########################
 #  CLOSE DAT FILE YO   #
 ########################
 FILE.close()

 ########################
 #  GENERATE PDF FILE   #
 ########################
 os.system("latex FinalGrades.tex")
 os.system("dvips FinalGrades.dvi")
 os.system("ps2pdf FinalGrades.ps")

if __name__ == '__main__':
 main()
