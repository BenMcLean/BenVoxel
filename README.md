# BenVoxel
BenVoxel files use sparse voxel octrees to compress voxel model geometry for file storage (with optional metadata) based on an open standard developed by Ben McLean.

The idea is to sacrifice processing speed to get a very small memory storage size for the actual geometry while keeping the implementation relatively simple and also allowing for extensive metadata to be optionally included. Compression is a concern for the geometry but not for the metadata because while uncompressed voxel model geometry data grows exponentially with model size, metadata doesn't.

There will be no license requirements restricting usage, but this format is designed for small voxel models intended for video games, animations or other entertainment, artistic or aesthetic use cases, so its design might not be ideal for unrelated academic, scientific, medical, industrial or military applications. Also, be aware that none of this has been engineered to provide security features (such as anti-cheat, checksums or length constraints for overflow protection) so use at your own risk.
## XML format
The BenVoxel standard describes two inter-related file formats. One is a binary format with the extension `.BEN` and the other is an XML format (recommended extension `.BEN.xml`) designed to contain all of the same information as the binary format but with the metadata kept human-readable. The XML format uses Z85 encoding for the geometry data. A game developer might keep their voxel models in the XML format during development but automatically convert to the binary format (potentially stripping out metadata) as part of their release pipeline.
### Schema
An XML schema for documentation purposes only (not providing validation for security) is included in the file `BenVoxel.xsd`. All the elements and attributes in the XML correspond directly to chunks or fields in the binary format.
### Versioning
Both the binary and XML formats include version information. In the binary format, this is a field in the `BENV` chunk. In the XML format, it's an attribute of the root `BenVoxel` element. The version should be compared alphanumerically as a string, with higher values indicating newer versions.

Implementations should rely on the Version attribute/field within the file for determining BenVoxel format feature support, not the schema version.
## Binary format
The BenVoxel binary format is based in concept on the Resource Interchange File Format (RIFF) introduced by Microsoft and IBM in 1991. This type of file is divided into chunks.
### Type definitions
All types are little-endian.

Three string types are used:
- `FourCC`: 4 byte ASCII chunk identifiers.
- `KeyString`: Starts with one unsigned byte for length, followed by a UTF-8 string of that length.
- `ValueString`: Starts with an unsigned 32-bit integer for length, followed by a UTF-8 string of that length.
### Chunks
All chunks have:
- 4 bytes: an ASCII identifier for this chunk (examples are "`FMT `" and "`DATA`"; note the space in "`FMT `").
- 4 bytes: an unsigned 32-bit integer with the length of this chunk (except this field itself and the chunk identifier).
- variable-sized field: the chunk data itself, of the size given in the previous field.
- a pad byte, if the chunk's length is not even. This maintains 16-bit alignment, following the convention established by the RIFF format. While less crucial for modern systems, this is maintained for historical reasons and potential performance benefits on some architectures.

This applies to ***all*** chunks, so this information won't be repeated in the individual chunk type descriptions.
#### `BENV` chunk (Root)
BenVoxel binary files start with a `BENV` chunk which contains the entire file and corresponds to the `<BenVoxel/>` root element in the XML format. It contains:
- `Version`: One `KeyString` for version information. Higher alphanumeric comparison indicates higher version.
- Compressed with zlib:
  - `Global`: One `DATA` chunk for global metadata. (optional)
  - `Count`: One unsigned 16-bit integer for the number of models.
  - For each model:
    - `Name`: One `KeyString` for the model name, expected to be unique among models within the file.
    - `Model`: One `MODL` chunk.

The zlib-compressed data is in the standard zlib format, including the 2-byte zlib header and 4-byte Adler-32 checksum. The compressed data should be decompressed before parsing the contained chunks. The size of the compressed data can be determined by subtracting the size of the Version field (the content of its 1-byte length field plus 1) from the `BENV` chunk size.
#### `DATA` chunk (Metadata)
Corresponds to the `<Metadata/>` element in the XML format. It contains:
- `Properties`: One `PROP` chunk. (optional)
- `Points`: One `PT3D` chunk. (optional)
- `Palettes`: One `PALC` chunk. (optional)
#### `MODL` chunk (Model)
Corresponds to the `<Model/>` element in the XML format. It contains:
- `Metadata`: One `DATA` chunk. (optional)
- `Geometry`: One `SVOG` chunk.
#### `PROP` chunk (Properties)
Corresponds to one or more `<Property/>` elements in the XML format. It contains:
- `Count`: One unsigned 16-bit integer for the number of properties.
- For each property:
  - `Name`: One `KeyString` for the property name, expected to be unique within this chunk.
  - `Value`: One `ValueString` for the property value.
#### `PT3D` chunk (Points)
Corresponds to one or more `<Point/>` elements in the XML format. It contains:
- `Count`: One unsigned 16-bit integer for the number of points.
- For each point:
  - `Name`: One `KeyString` for the point name, expected to be unique within this chunk.
  - `Coordinates`: Three signed 32-bit integers for the X, Y and Z coordinates.
#### `PALC` chunk (Palettes)
Corresponds to one or more `<Palette/>` elements in the XML format. It contains:
- `Count`: One unsigned 16-bit integer for the number of palettes.
- For each palette:
  - `Name`: One `KeyString` for the palette name, expected to be unique within this chunk.
  - `Length`: One unsigned byte representing the number of colors minus one, with a range of 0-255 representing 1-256 colors. A value of `0` indicates `1` colors, and a value of `255` indicates `256` colors. This range includes the background color at index zero while the rest of the indices correspond to the voxel payload bytes.
  - `Colors`: A series of `Length` 32-bit unsigned integers representing colors in ARGB format.
  - `HasDescriptions`: One unsigned byte with value `0` to indicate no descriptions xor any other value to include descriptions.
  - `Descriptions`: A series of `Length` `ValueString`s describing the colors. Only included if `HasDescriptions` is not `0`. A description should stay associated with the color it describes even when the colors or their order changes. The first line of the description should be a short, human-readable message such as could be displayed as a tooltip in an editor to remind the user what this color or material value is being used for without crowding the screen. Additional data not intended to be displayed in such a context, such as settings for an associated material, can be placed after the first line. Editors not actually using such additional data should still preserve it when saving and loading.
#### `SVOG` chunk (Geometry)
Stands for "**S**parse **V**oxel **O**ctree **G**eometry". Corresponds to the `<Geometry/>` element in the XML format. It contains:
- `Size`: Three unsigned 16-bit integers for the (X) width, (Y) depth and (Z) height of the model. The size coordinates are outside the model and geometry data outside these bounds may be discarded. Dimensions of 0 are invalid. Setting one of the dimensions to the maximum extent of 65,535 will result in assignable coordinates for that axis maxing out at 65,534 to keep the implementation simple.
- `Geometry`: A variable length series of bytes which encodes the voxels according to the "Geometry" section of this document.
## Geometry
Both the XML and binary formats use this sparse voxel octree format. The XML format specifically uses Z85 encoding for the geometry data to ensure valid XML characters, while the binary format stores this data raw, without encoding. The binary format prefixes the model size to this geometry data while the XML format includes the model size in separate XML attributes instead.
### Voxels
An individual voxel is defined as having four data elements.
#### Coordinates
The first three data elements of a voxel are 16-bit unsigned integers for the X, Y and Z coordinates. Negative coordinates and coordinates larger than 65,534 are unsupported.
#### Payload
The fourth data element of a voxel is the payload of one byte for the index to reference a color or material, where 0 is reserved for an empty or absent voxel, leaving 255 usable colors or materials.
### Models
Models (sets of voxels) are limited by 16-bit unsigned integer bounds, so valid geometry can range from coordinates of 0 to 65,534. Model contents are expected to be following the MagicaVoxel convention, which is Z+up, right-handed, so X+ means right/east in width, Y+ means forwards/north in depth and Z+ means up in height. Models are expected to be aligned so that their lowest edge occupies coordinate 0 on all three axes.
#### Octree
To serialize a model, geometry is structured as a sparse voxel octree for compression, so that the coordinates of the voxels are implied from their positions in the octree and empty spaces are not stored.

The octree has a fixed depth of 16 levels, corresponding to the 16 bits of addressable space in the unsigned 16-bit integer spatial coordinates. The first 15 levels consist of only Branch nodes, while the 16th and final level contains only Leaf nodes.
### Nodes
There are four node types, which include one type of branch and three types of leaves.
#### Header
All nodes start with a 1-byte header, composed of bits from left to right:
- Header bits 7-6: Node type indicator
  - `00`: Branch
  - `01`: 1-byte payload Leaf
  - `10`: 2-byte payload Leaf
  - `11`: 8-byte payload Leaf
- Header bits 5-3:
  - For Branch nodes: number of children (1-8) minus one.
  - For 2-byte Leaf nodes: ZYX octant of the foreground voxel.
  - For other node types: unused.
- Header bits 2-0: ZYX octant indicator
  - These bits encode the node's position relative to its parent in ascending Z, Y, X order.
  - `0` represents the negative direction and `1` represents the positive direction for each axis.
  - Examples:
    - `000`: (-X, -Y, -Z) octant
    - `111`: (+X, +Y, +Z) octant
    - `101`: (+X, -Y, +Z) octant
#### Branch nodes
In Branch nodes, the header byte is followed by the child nodes. On the 16th (last) level of the octree, all of the children will be Leaf nodes, but the children will all be Branch nodes on every other level.
#### Leaf nodes
##### 1-byte payload Leaf nodes
These represent a 2x2x2 voxel cube of all the same color or material. The header byte is followed by one payload byte, which should fill in all eight voxels.
##### 2-byte payload Leaf nodes
These represent a 2x2x2 voxel cube in which all the voxels are the same except one, called the foreground voxel. The header byte is followed by two payload bytes: the first for the foreground voxel and then the second for the background voxels.

The octant/position of the foreground voxel is indicated by coordinates in header bits 5-3, using the same ZYX octant encoding scheme as described in the Header section above.

The background voxel value should be repeated in all octants/positions except for the foreground voxel.
##### 8-byte payload Leaf nodes
These represent a 2x2x2 voxel cube of any arbitrary values. In 8-byte Leaf nodes, the header byte is followed by the eight payload bytes of a 2x2x2 voxel cube in ascending Z, Y, X order from left to right, with 0 representing empty voxels.
### Empty models
An empty model would be represented by the hexadecimal string `0000000000000000000000000000004000` which is structured as follows:
- 15 bytes for branch node headers which are all `0`.
- 1 byte for a leaf node header with hexadecimal value `0x40`
- 1 byte for the payload of the leaf node

The 15 branch node headers correspond to the 15 levels of the octree needed to address a space with 16-bit integer coordinates (2^16 = 65,536). The 16th level is represented by the leaf node.
