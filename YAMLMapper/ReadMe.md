# YAML Direct Mapping Library


This library gives the ability that enables direct mapping from yaml to C variable.

Example:

Sample YAML File:
```YAML
sprite:
	cell_size: [64,64] #width, height in pixels
```
Code For Mapping:
```C
YAMLMapper *spriteMeta = new YAMLMapper();
SDL_Point spriteSize;
spriteMeta->addMapping("sprite:cell_size", &spriteSize.x, 0);
spriteMeta->addMapping("sprite:cell_size", &spriteSize.y, 1);
spriteMeta->parse("sample.yml");
```

Currently Provided Features:
- Mappings of scalars to scalars
- Values of int, float, double, string
- Flow sequences

Features Not Supported Yet:
- Sequence of scalars
- Sequence of mappings
- Sequence of sequences
- Mappings of scalars to sequences

Features Not Tried Yet:
- Mapping of mappings

For detailed info: http://yaml.org/spec/1.1/#id857181
