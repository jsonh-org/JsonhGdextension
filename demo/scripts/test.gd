extends Node

func _ready() -> void:
	# README example
	const jsonh:String = "[hello, world]"
	var value:Variant = Jsonh.parse_element(jsonh).value
	print(value) # ["hello", "world"]
	print(type_string(typeof(value))) # Array
	
	# Benchmarks
	await get_tree().create_timer(1.0).timeout
	benchmark(1.0, true)
	benchmark(1.0, false)
#end

func benchmark(duration:float, use_jsonh:bool)->void:
	const json:String = "{ \"hello\": \"world\", \"data\": [ 1, 2, 3 ] }"
	
	if use_jsonh:
		print("JSONH:")
	else:
		print("JSON:")
	#end
	
	var counter:int = 0
	var start_timestamp:int = Time.get_ticks_msec()
	while (Time.get_ticks_msec() - start_timestamp) < (duration * 1000):
		if use_jsonh:
			var value:Variant = Jsonh.parse_element(json).value
		else:
			var value:Variant = JSON.parse_string(json)
		#end
		counter += 1
	#end
	print(Time.get_ticks_msec() - start_timestamp, "ms")
	print(counter, " times")
