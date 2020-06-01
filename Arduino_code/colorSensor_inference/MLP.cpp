//////////////////////////////////////////////////////////////////////////////
//
//  MLP.cpp - Artificial Neural Network architectures for arduino
//  Copyright (c) 2016 Caio Benatti Moretti <caiodba@gmail.com>
//               http://www.moretticb.com/Neurona
//
//  Last update: 16 July 2016
//
//  This library is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////////////

#include "Arduino.h"

#include <avr/pgmspace.h>


const byte LOGISTIC = 0;
const byte TANH = 1;
const byte LINEAR = 2;



class MLP {
	public:
	
		/**
		 * Constructor.
		 * Initializes a Multi-Layer Perceptron (operation mode) from a trained topology with the adjusted synaptic weights, This network can be used for classification/regression.
		 * @param inputs the number of inputs to feed the network.
		 * @param outputs the number of network outputs.
		 * @param topology an array indicating the size of each layer (including outputs), ending with -1.
		 * @param activFunc the activation function to be used.
		 * @param weights an array with the adjusted weights (obtained in training).
		 * @param usingPGM whether weights is a PROGMEM variable.
		 * @see LOGISTIC
		 * @see TANH
		 * @see LINEAR
		 */
    MLP(byte inputs, byte outputs, int *topology, byte activFunc, double const *weights, boolean usingPGM)
    {
	_inflection = 1.0;
	_activFunc = activFunc;
	_inputs = inputs;
	_outputs = outputs;
	_layerSizes = topology;
	_PGM = usingPGM;
	
	_initW = weights;
	
	_yOffset = 1;//reusing variables
	_iOffset = _layerSizes[0];
	
	do{
		if(_layerSizes[_yOffset] > _iOffset)
			_iOffset = _layerSizes[_yOffset];
	} while (_layerSizes[++_yOffset]>-1);
	
	_iArray = (double*) malloc(sizeof(double)*_iOffset);
	_yArray = (double*) malloc(sizeof(double)*_iOffset);
	
	_layers = _yOffset;
	_iOffset = _yOffset = 0;//actual initialization
    }
		
		/**
		 * Logistic activation function
		 */



		static const byte LOGISTIC ;
		
		/**
		 * Hyperbolic Tangent activation function
		 */
		static const byte TANH;
		
		/**
		 * Linear activation function
		 */
		static const byte LINEAR;
		
double * forward(double *sample){
	return getY(_inputs,_layers-1,sample);
}		


int getActivation(double *sample){
	double *output = getY(_inputs,_layers-1,sample);
	int maxIndex = 0;
        int outSize=_layerSizes[_layers-1];
	for(int i=1;i<outSize;i++){
		if(output[i]>output[maxIndex])
			maxIndex=i;
	}
	return maxIndex;
}

		
	private:
		byte _inputs, _outputs, _layers, _iOffset, _yOffset, _activFunc;
		boolean _PGM;
		int* _layerSizes;
		double _inflection;
		double const * _initW;
		double* _iArray;
		double* _yArray;
				
		double activation(double x){
	if(_activFunc==0)
		return 1.0/(1.0+exp(-_inflection*x));
	else if(_activFunc==1)
		return (1.0-exp(-_inflection*x))/(1.0+exp(-_inflection*x));
	else
		return x; //Consider linear function when activation function is unknown
}

double getWeight(int layer, int neuron, int weight, int inputs){
        int i, lastLayer, index=0;
        for(i=0;i<layer;i++){
                lastLayer = i==0?inputs:_layerSizes[i-1];
                index += _layerSizes[i]*(lastLayer+1);
        }
        lastLayer = layer==0?inputs:_layerSizes[layer-1];
        index += (lastLayer+1)*neuron+weight;
		return _PGM ? pgm_read_float(_initW + index) : _initW[index];
}		

double * getI(int inputs, int layer, double *sample){
        int i, j, ISize = _layerSizes[layer], wLen = (layer<1?inputs:_layerSizes[layer-1])+1;
        double *I = _iArray;
        _iOffset=ISize;

        double *prevI = layer<1 ? sample : getY(inputs, layer-1, sample);

        for(i=0;i<ISize;i++){
                I[i] = 0.0;
                for(j=0;j<wLen;j++)
                        I[i] += getWeight(layer,i,j,inputs) * prevI[j];
        }

        return I;
}		
double * getY(int inputs, int layer, double *sample){
        int i, last = _layerSizes[layer+1]==-1, YSize = _layerSizes[layer]+!last;
        double *I = getI(inputs, layer, sample);
        double *Y = _yArray;
        _yOffset=YSize;

        for(i=0;i<YSize;i++)
                if(last)
                        Y[i] = activation(I[i]);
                else
                        Y[i] = i==0 ? -1.0 : activation(I[i-1]);

        return Y;
}		
};











/**
 * Multi-Layer Perceptron Artificial Neural Network.
 *
 * This Artificial Neural Network architecture can be used to perform classification, regression or time-series prediction.
 */









