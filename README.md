# Ben McLean Experimental Voxel Model File Format
## Geometry
### Voxels
An individual voxel is defined as having four data elements.
#### Coordinates
The first three data elements of a voxel are 16-bit unsigned integers for the X, Y and Z coordinates. Negative coordinates and coordinates larger than 65,534 are unsupported.
#### Payload
The fourth data element of a voxel is the payload of one byte for the index to reference a color or material, where 0 is reserved for an empty or absent voxel, leaving 255 usable colors or materials.
### Models
Models (sets of voxels) are expected to be following the MagicaVoxel convention, which is Z+up, right-handed, so X+ means right/east, Y+ means forwards/north and Z+ means up. Models are expected to be aligned so that their lower edge is 0 on all three axes.

To serialize a model, geometry is structured as a sparse voxel octree for efficient compression, so that the coordinates of the voxels are implied from their positions in the octree and empty spaces are not stored.
### Nodes
There are four node types, which include one type of branch and three types of leaves.
#### Header
All nodes start with a 1-byte header, composed of bits from left to right:
* Header bits 7-6: Node type indicator
  * `00`: Branch
  * `01`: 1-byte payload Leaf
  * `10`: 2-byte payload Leaf
  * `11`: 8-byte payload Leaf
* Header bits 5-3: For Branch, number of children (1-8) minus one. For 2-byte Leaf, ZYX octant of the foreground voxel. Note that these bits are only used when header bit 6 is 0.
* Header bit 2: Z of octant
* Header bit 1: Y of octant
* Header bit 0: X of octant
#### Branch nodes
In Branch nodes, the header byte is followed by the child nodes. On the 16th (last) level of the octree, all of the children will be Leaf nodes, but the children will all be Branch nodes on every other level.
#### Leaf nodes
##### 1-byte payload Leaf nodes
These represent a 2x2x2 voxel cube of all the same color or material. The header byte is followed by one payload byte, which should fill in all eight voxels.
##### 2-byte payload Leaf nodes
These represent a 2x2x2 voxel cube in which all the voxels are the same except one, called the foreground voxel. The header byte is followed by two payload bytes: the first for the foreground voxel and then the second for the background voxel. The octant/position of the foreground voxel is indicated by coordinates in header bits 5-3 in ascending Z, Y, X order from left to right. So this indicates that the background vovel value should be repeated seven times: in all octants/positions except for the foreground voxel.
##### 8-byte payload Leaf nodes
These represent a 2x2x2 voxel cube of any arbitrary values. In 8-byte Leaf nodes, the header byte is followed by the eight payload bytes of a 2x2x2 voxel cube in ascending Z, Y, X order from left to right, with 0 representing empty voxels.
### Empty models
An empty model would be represented by the hexadecimal string `0000000000000000000000000000004000` which is 15 bytes for branch node headers which are all 0, then 1 byte for a leaf node header with hexadecimal value `0x40`, then 1 byte for the payload of the leaf node.
