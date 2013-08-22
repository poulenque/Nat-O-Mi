
This tool was made to replace a physicist laboratory assistant who may want to use terrible tools popular in the buisness world (such as Excel).


inputFileFormat :

VAR_NAME should be written in this format : VAR_NAME [UNIT] [ERROR] [FORMULA]

UNIT    : this is a tool for physicist, you have to put units in SI (meter,m,Km,second,s,Kg,g etc...)

ERROR   : is of type CONSTANT or VARIABLE : if it is variable, you must write a VAR_NAME_ERROR column

FORMULA : formula is optional : it is used when calculated with values from mesured or calculated data. It will generate 




VAR_0_NAME [UNIT] [ERROR] [FORMULA]     /tab or /space    VAR_1_NAME [UNIT] [ERROR] [FORMULA]
value                                   /tab or /space    value                              
value                                   /tab or /space    value                              
value                                   /tab or /space    value                              
value                                   /tab or /space    value                              
value                                   /tab or /space    value                              
...                                                                                          





This tool include for now :

- pretty much nothing


It will include :

- plotting curves with GNUplot
	- 2D/3D graphs
	- color images
	- animated graph

- calculating new column from mesured data
	- generate error

- make some output in latex
	- table

- wav file generator

- Unit Checker


If we have time, may never happen :

- define some new units ?
- export from other fileformat to our format




