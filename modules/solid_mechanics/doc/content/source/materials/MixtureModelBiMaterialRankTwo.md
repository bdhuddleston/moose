# MixtureModelBiMaterialRankTwo

This class implements a mixture model material from two materials. 


!syntax description /Materials/MixtureModelBiMaterialRankTwo

## Overview

MixtureModelBiMaterial is designed to take a material property which is calculated by two different material objects 
with different base names and mix them into a single material property based on a field variable. 
An example would be two objects that both calculate stress on a block with base names "A" 
and "B". The mixture model would take the material properties "A_stress" and "B_stress" and
mix them into a "stress" material property for the kernel to solve. 

The model uses a simple rule of mixtures to combine the two properties. 

## Use for Modeling Mechanical Materials

Stress materials will need to have a MixtureModelBiMaterialRankTwo for stress, and a 
MixtureModelBiMaterialRankFour for the jacobian, "jacmult". 

## Example Input File Syntax

MixtureModelBiMaterial requires two pieces to work: a field variable ranging from 0 to 1 which defines the phase
fraction of the primary material and two material objects which generate a property with the same name, one for each 
physical material. A base name should be assigned to each material object. These base names are required in the 
MixtureModelBiMaterial object to point to the two properties which should be mixed. 

!listing modules/solid_mechanics/test/tests/mixture_model/three_element.i block=Materials/stress_mixture

!syntax parameters /Materials/MixtureModelBiMaterialRankTwo

!syntax inputs /Materials/MixtureModelBiMaterialRankTwo

!syntax children /Materials/MixtureModelBiMaterialRankTwo
