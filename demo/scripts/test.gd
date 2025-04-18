extends Node

@onready var label: Label = $Label

func _ready() -> void:
	var jsonh:String = "[hello, world]"
	
	var value:Variant = Jsonh.parse_element(jsonh).value
	print(value) # ["hello", "world"]
	print(type_string(typeof(value))) # Array
