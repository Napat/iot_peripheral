
output
```
# Deserialize json string to c struct-----------------------
{    "name": "ASUS (\"Monitor\") MX34VQ",    "monitor": {        "type":          "IPS",        "width":          3440,        "height":         1440,        "interlace_vga":    false,        "frame rate":     100    }}
name = ASUS ("Monitor") MX34VQ
type = IPS
width = 3440
height = 1440
interlace_vga = false
framerate = 100.000000

# Srialize c struct to json string-----------------------
{
	"name":	"ASUS (\"Monitor\") MX34VQ",
	"monitor":	{
		"type":	"IPS",
		"width":	3440,
		"height":	1440,
		"interlace_vga":	false,
		"frame rate":	100
	}
}

## Minify json string
{"name":"ASUS (\"Monitor\") MX34VQ","monitor":{"type":"IPS","width":3440,"height":1440,"interlace_vga":false,"frame rate":100}}

# Deserialize json string to c struct-----------------------
{    "name": "ASUS (\"Monitor\") MX34VQ",    "monitor": {        "type":          "IPS",        "width":          3440,        "height":         1440,        "interlace_vga":    false,        "frame rate":     100    }}
name = ASUS ("Monitor") MX34VQ
...
```
