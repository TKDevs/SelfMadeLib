//--------------------------------------------------------------------------------------
//multiply matrix with value
float[][] multMatrix(float[][] m1, float value) { 
  for(int i = 0;i < m1.length;i++) {
    for(int j = 0;j < m1[0].length;j++) {
      m1[i][j] *= value;
    }
  }
  return m1;
}
//--------------------------------------------------------------------------------------
//multiply matrix with value
float[][] multMatrix(float value, float[][] m1) { 
  for(int i = 0;i < m1.length;i++) {
    for(int j = 0;j < m1[0].length;j++) {
      m1[i][j] *= value;
    }
  }
  return m1;
}
//--------------------------------------------------------------------------------------
//multiply matrix with matrix
float[][] multMatrix(float[][] m1, float[][] m2) {
  float[][] x = new float[m1.length][m2[0].length];

  for(int i = 0;i < x.length;i++) {
    for(int j = 0;j < x[0].length;j++) {
      float y = 0;
      for(int k = 0;k < m1[0].length;k++) {
        y += m1[i][k] * m2[k][j];
      }
      x[i][j] = y;
    }
  }
  return x;
}
//--------------------------------------------------------------------------------------
//dot product of a matrix and a value
float dotMatrix(float[][] m1, float value) {
  float x = 0;
  for(int i = 0;i < x;i++) {
    for(int j = 0;j < x;j++) {
      x += m1[i][j] * value;
    }
  }
  return x;
}
//--------------------------------------------------------------------------------------
//dot product of a matrix and a value
float dotMatrix(float value, float[][] m1) {
  float x = 0;
  for(int i = 0;i < x;i++) {
    for(int j = 0;j < x;j++) {
      x += m1[i][j] * value;
    }
  }
  return x;
}
//--------------------------------------------------------------------------------------
//dot product of a matrix and a value
float dotMatrix(float[][] m1, float[][] m2) {
  float x = 0;
  for(int i = 0;i < x;i++) {
    for(int j = 0;j < x;j++) {
      x += m1[i][j] * m2[i][j];
    }
  }
  return x;
}
//--------------------------------------------------------------------------------------
//transpose matrix
float[][] transMatrix(float[][] m1) { 
  float[][] x = new float[m1[0].length][m1.length];
  for(int i = 0;i < x.length;i++) {
    for(int j = 0;j < x[0].length;j++) {
      x[i][j] = m1[j][i];
    }
  }
  return x;
}
//--------------------------------------------------------------------------------------
//apply sigmoid on a matrix
float[][] sigmoid(float[][] m1) { 
  for(int i = 0;i < m1.length;i++) {
    for(int j = 0;j < m1[0].length;j++) {
      m1[i][j] = sigmoid(m1[i][j]);
    }
  }
  return m1;  
}
//--------------------------------------------------------------------------------------
//sigmoid function
float sigmoid(float x) {
  return 1/(1 + exp(-x)); // exp returns euler's number raised to the power of -x
}
//--------------------------------------------------------------------------------------
//subtract every number in a matrix from a value individually
float[][] subMatrix(float value, float[][] m1) {
  for(int i = 0;i < m1.length;i++) {
    for(int j = 0;j < m1[0].length;j++) {
      m1[i][j] = value - m1[i][j];
    }
  }
  return m1;
}
//--------------------------------------------------------------------------------------
//subtract a value individually from every number in a matrix
float[][] subMatrix(float[][] m1, float value) {
  for(int i = 0;i < m1.length;i++) {
    for(int j = 0;j < m1[0].length;j++) {
      m1[i][j] = m1[i][j] - value;
    }
  }
  return m1;
}
//--------------------------------------------------------------------------------------
//subtract a matrix from another matrix
float[][] subMatrix(float[][] m1, float[][] m2) {
  float[][] x = new float[m1.length][m1[0].length];
  for(int i = 0;i < m1.length;i++) {
    for(int j = 0;j < m1[0].length;j++) {
      x[i][j] = m1[i][j] - m2[i][j];
    }
  }
  return x;
}
//--------------------------------------------------------------------------------------
//add a value to a matrix
float[][] addMatrix(float[][] m1, float value) {
  for(int i = 0;i < m1.length;i++) {
    for(int j = 0;j < m1[0].length;j++) {
      m1[i][j] = value + m1[i][j];
    }
  }
  return m1;
}
//--------------------------------------------------------------------------------------
//add a value to a matrix
float[][] addMatrix(float value, float[][] m1) {
  for(int i = 0;i < m1.length;i++) {
    for(int j = 0;j < m1[0].length;j++) {
      m1[i][j] = value + m1[i][j];
    }
  }
  return m1;
}
//--------------------------------------------------------------------------------------
//add a matrix to another
float[][] addMatrix(float[][] m1, float[][] m2) {
  float[][] x = new float[m1.length][m1[0].length];
  for(int i = 0;i < m1.length;i++) {
    for(int j = 0;j < m1[0].length;j++) {
      x[i][j] = m1[i][j] + m2[i][j];
    }
  }
  return x;
}
