-- These values can be accessed through 'theTuning'

-- Strength of the springs holding the engines together
PodSpringStrength = {
	type = "float",
	value = 2.2
}
-- Damping of the springs holding the engines together
PodSpringDamping = {
	type = "float",
	value = 0.03
}

-- Base power for an engine
EnginePower = {
	type = "float",
	value = 100
}

-- Constant for amount of drag applied to things
Drag = {
	type = "float",
	value = 1.1
}

-- Constant for amount of lift applied to things
Lift = {
	type = "float",
	value = 0.5
}

-- Air friction applied to the pod engines
EngineDrag = {
	type = "float",
	value = 0.9
}

-- Air friction applied to the pod
PodDrag = {
	type = "float",
	value = 1.5
}

-- Air friction applied to the pod
PodRopeLength = {
	type = "float",
	value = 10.0
}

-- Maximum thrust allowed by ai
AIDifficulty = {
	type = "float",
	value = 0.85
}