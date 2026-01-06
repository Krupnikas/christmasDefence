extends Node2D
class_name BulletBase
## Base class for all bullet/projectile types

@export var speed: float = 400.0
@export var lifetime: float = 5.0

var direction: Vector2 = Vector2.RIGHT
var damage: float = 10.0
var source_cannon: CannonBase = null

var timer: float = 0.0


func _ready() -> void:
	add_to_group("bullets")

	# Rotate sprite to face direction
	rotation = direction.angle()


func _process(delta: float) -> void:
	# Move in direction
	global_position += direction * speed * delta

	# Lifetime check
	timer += delta
	if timer >= lifetime:
		queue_free()


func _on_body_entered(body: Node2D) -> void:
	if body.is_in_group("enemies") and body.has_method("take_damage"):
		body.take_damage(damage, source_cannon)
		_on_hit(body)


func _on_hit(_target: Node2D) -> void:
	# Override for special effects
	queue_free()
