<img src="https://github.com/jsonh-org/Jsonh/blob/main/IconUpscaled.png?raw=true" width=180>

[![Godot Asset Library](https://img.shields.io/github/v/release/jsonh-org/JsonhGdextension.svg?style=flat-square&label=Godot%20Asset%20Library&logo=godotengine)](https://godotengine.org/asset-library/asset/3950)

**JSON for Humans.**

JSON is great. Until you miss that trailing comma... or want to use comments. What about multiline strings?
JSONH provides a much more elegant way to write JSON that's designed for humans rather than machines.

Since JSONH is compatible with JSON, any JSONH syntax can be represented with equivalent JSON.

JsonhGdextension is an implementation of [JSONH v1](https://github.com/jsonh-org/Jsonh).

## Example

```jsonh
{
    // use #, // or /**/ comments
    
    // quotes are optional
    keys: without quotes,

    // commas are optional
    isn\'t: {
        that: cool? # yes
    }

    // use multiline strings
    haiku: '''
        Let me die in spring
          beneath the cherry blossoms
            while the moon is full.
        '''
    
    // compatible with JSON5
    key: 0xDEADCAFE

    // or use JSON
    "old school": 1337
}
```

## Usage

Everything you need is contained within `Jsonh`:

```gdscript
var jsonh:String = "[hello, world]"
var value:Variant = Jsonh.parse_element(jsonh).value
print(value) # ["hello", "world"]
```

## Dependencies

- C++20
- Godot 4.4
- [jsonh-org/JsonhCpp](https://github.com/jsonh-org/JsonhCpp) (v4.2)

## Limitations

### Limited API

Due to the limitations of GDExtension and GDScript, only one static method (`Jsonh.parse_element`) is exposed.

### Android support

JsonhGdextension does not currently support Android due to an issue with nlohmann/json. See [nlohmann/json#4736](https://github.com/nlohmann/json/pull/4736).