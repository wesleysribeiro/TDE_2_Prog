/* Biblioteca de funcoes que realizam diversos calculos de Geometria Analitica */



float prod_escalar(float *x, float *y, float *z){ 
	return x[0]*x[1] + y[0]*y[1] + z[0]*z[1];
}


void prod_vet(float *x, float *y, float *z){   /* Realiza o calculo de produto vetorial e armazena nos vetores x, y, z */
	x[2] = y[0]*z[1] - z[0]*y[1];
	y[2] = z[0]*x[1] - x[0]*z[1];
	z[2] = x[0]*y[1] - y[0]*x[1];
}

float prod_misto(float *x, float *y, float *z){
	return x[0]*y[1]*z[2] + y[0]*z[1]*x[2] + z[0]*x[1]*y[2] - y[0]*x[1]*z[2] - x[0]*z[1]*y[2] - z[0]*y[1]*x[2];
}

float dist_pontos(float *x, float *y, float *z){
	return sqrt(pow(x[0] - x[1], 2.0) + (pow(y[0] - y[1], 2.0)) + (pow(z[0] - z[1], 2.0)));
}

float dist_ponto_reta(float *x, float *y, float *z){
	x[3] = y[0]*(z[1] - z[2]) - z[0]*(y[1] - y[2]);	
	y[3] = z[0]*(x[1] - x[2]) - x[0]*(z[1]-z[2]);
	z[3] = x[0]*(y[1] - y[2])- y[0]*(x[1] - x[2]);
	return sqrt(pow(x[3], 2.0) + pow(y[3], 2.0) + pow(z[3], 2.0))/sqrt(pow(x[0], 2.0) + pow(y[0], 2.0) + pow (z[0], 2.0));
}

float dist_retas(float *x, float *y, float *z){
	x[3] = y[0]*(z[1] - z[2]) - z[0]*(y[1] - y[2]);	
	y[3] = z[0]*(x[1] - x[2]) - x[0]*(z[1]-z[2]);
	z[3] = x[0]*(y[1] - y[2])- y[0]*(x[1] - x[2]);
	return sqrt(pow(x[3], 2.0) + pow(y[3], 2.0) + pow(z[3], 2.0))/sqrt(pow(x[0], 2.0) + pow(y[0], 2.0) + pow (z[0], 2.0));
}

float dist_retas_reversas(float *x, float *y, float *z){
	float prod_misto;
	x[4] = y[0]*z[1] - z[0]*y[1];
	y[4] = z[0]*x[1] - x[0]*z[1];
	z[4] = x[0]*y[1] - y[0]*x[1];	
	prod_misto = x[0]*y[1]*(z[2] - z[3]) + y[0]*z[1]*(x[2] - x[3]) + z[0]*x[1]*(y[2] - y[3]) - y[0]*x[1]*(z[2] - z[3]) - x[0]*z[1]*(y[2] - y[3]) - z[0]*y[1]*(x[2] - x[3]);
	if (prod_misto < 0)
		prod_misto *= -1;
	return prod_misto/sqrt(pow(x[4], 2.0) + pow(y[4], 2.0) + pow(z[4], 2.0));
}

float dist_reta_plano(float *x, float *y, float *z, float *d){
	float modulo;
	modulo = x[0]*x[1] + y[0]*y[1] + z[0]*z[1] + d[0];
	if (modulo < 0)
		modulo *= -1;
	return	modulo/sqrt(pow(x[0], 2.0) + pow(y[0], 2.0) + pow(z[0], 2.0));
}

float dist_ponto_plano(float *x, float *y, float *z, float *d){
	float modulo;
	modulo = x[0]*x[1] + y[0]*y[1] + z[0]*z[1] + d[0];
	if (modulo < 0)
		modulo *= -1;
	return modulo/sqrt(pow(x[0], 2.0) + pow(y[0], 2.0) + pow(z[0], 2.0));
}

