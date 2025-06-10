# Mixture Model Bi-Material Real

!syntax description /Materials/MixtureModelBiMaterialReal

## Description

This class implements a mixture model material from two materials. 

It is designed to take a material property which is calculated by two different objects with 
different base names and mix them into a single material property based on a field variable. 
An example would be two objects that both calculate stress on a block with base names "A" 
and "B". The mixture model would take the material properties "A_stress" and "B_stress" and
mix them into a "stress" material property for the kernel to solve. 

### Mixture Model

Currently, this class only implements a simple rule of mixtures. It expects a field variable,
 $m$, ranging from 0 to 1, and it calculates the mixed property as 
\begin{equation}
   m * A_prop + (1 - m) * B_prop
\end{equation}

### Use for Modeling Mechanical Materials

Stress materials will need to have a MixtureModelBiMaterialRankTwo for stress, and a 
MixtureModelBiMaterialRankFour for the jacobian, "jacmult". 

## Example Input File Syntax

!listing modules/solid_mechanics/test/tests/mixture_model/three_element.i block=Materials/stress_mixture

!listing modules/solid_mechanics/test/tests/mixture_model/read_mesh.i block=Materials/stress_mixture

!syntax parameters /Materials/MixtureModelBiMaterialRankTwo

!syntax inputs /Materials/MixtureModelBiMaterialRankTwo

!syntax children /Materials/MixtureModelBiMaterialRankTwo
