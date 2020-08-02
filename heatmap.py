import matplotlib.pyplot as plt
import numpy as np
import seaborn as sb

def matrix_inicialization(mat,lin, col,temp):
  for l in range(lin):
    for c in range(col):
      mat[l][c][0] = (l*(lin - l -1)) * (c*(col - c -1))
  max_value = float(mat.max())
  mat_test = np.zeros((lin,col), dtype=np.float64)
  for l in range(lin):
    for c in range(col):
      mat[l][c][0] /= max_value
      mat_test[l][c] = mat[l][c][0] 
  heat_map = sb.heatmap(mat_test)
  plt.title('heatmap_%s' %(0*temp))
  plt.show()

def matrix_mapping(mat,lin,col,temp,t):
  mat_test = np.zeros((lin,col), dtype=np.float64)
  for l in range(1,lin-1):
    for c in range(1,col-1):
      mat[l][c][temp] = mat[l][c][temp-1] + C_xy*((mat[l+1][c][temp-1])+(mat[l-1][c][temp-1])-2.*(mat[l][c][temp-1]))+C_xy*((mat[l][c+1][temp-1])+(mat[l][c-1][temp-1])-2.*(mat[l][c][temp-1]))
      mat_test[l][c] = mat[l][c][temp]     
  heat_map = sb.heatmap(mat_test,vmin=0,vmax=1)
  plt.title('heatmap_%s' %(t*temp))
  plt.show()

def matrix_temp(mat,lin,col,temp):
  for t in range(1,temp+1):
    matrix_mapping(mat,lin,col,t,temp)

def print_all_matrix(mat,lin,col,temp):
  print("\n--------------- Matrix Inicial: ----------------")
  for t in range(temp+1):
    print("\n--------------- Matrix temp_%1.0f: ----------------\n"%(t*temp))
    for l in range(lin):
      for c in range(col):
        print("%1.2f"%(mat[l][c][t]), end=" ")
      print()  
      
#----------------------------------- "MAIN" --------------------------------------------#
C_xy = 0.45
lin = int(input("Lines: "))
col = int(input("Colluns: "))
temp = 10
mat = np.zeros((lin,col,temp+1), dtype=np.float64)

matrix_inicialization(mat,lin,col,temp)

matrix_temp(mat,lin,col,temp)

print_all_matrix(mat,lin,col,temp)





