# MikkTSpace

This repository contains code used to generate test cases for the
[MikkTSpace Rust bindings](https://github.com/gltf-rs/mikktspace).

The idea is to use the reference implementation of the
[Mikkelsen Tangent Space Algorithm](http://mikktspace.com/) to generate tangents
for a mesh and output them as a Rust code to be used directly in a test case.

It is nothing more than a throwaway code for a single purpose - it currently
transforms a single hardcoded mesh copied from an example in the Rust bindings
project. That said, it would probably be nice to extend it to load OBJs at some
point, allowing to generate more test cases.

