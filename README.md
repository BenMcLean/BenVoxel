# Ben McLean Experimental Voxel Model File Format
## Geometry
### Voxels
An individual voxel is defined as having four data elements.
#### Coorinates
The first three data elements of a voxel are 16-bit unsigned integers for the X, Y and Z coordinates. Negative coordinates and coordinates larger than 65,534 are unsupported.
#### Payload
The fourth data element of a voxel is the payload of one byte for the index to reference a color or material, where 0 is reserved for an empty or absent voxel, leaving 255 usable colors or materials.
### Models
Models (sets of voxels) are expected to be following the MagicaVoxel convention, which is Z+up, right-handed, so X+ means right/east, Y+ means forwards/north and Z+ means up. Models are expected to be aligned so that their lower edge is 0 on all three axes.

To serialize a model, geometry is structured as a sparse voxel octree for efficient compression, so that the coordinates of the voxels are implied from their positions in the octree and only the payload byte is necessary to be actually stored for each individual voxel.
### Nodes
There are two types of nodes in the octree: Branch and Leaf.
#### Header
All nodes start with a 1-byte header, composed of bits from left to right:
* Header bit 7: Node Type. 0 for Branch, 1 for Leaf.
* Header bit 6: Unused
* Header bits 5-3: For Branch only, number of children (1-8) minus one
* Header bit 2: Z of octant
* Header bit 1: Y of octant
* Header bit 0: X of octant
#### Branch nodes
In Branch nodes, the header byte is followed by the child nodes. On the 16th (last) level of the octree, all of the children will be Leaf nodes, but the children will all be Branch nodes on every other level.
#### Leaf nodes
In Leaf nodes, the header byte is followed by the eight payload bytes of a 2x2x2 voxel cube in ascending Z, Y, X order from left to right, with 0 representing empty voxels.
### Empty models
An empty model would be represented by the hexadecimal string `000000000000000000000000000000800000000000000000` which is 15 bytes for branch node headers which are all 0, then 1 byte for a leaf node header with hexadecimal value `0x80`, then 8 bytes which are all 0 for one empty 2x2x2 voxel cube.
