extends CannonBase
class_name MinerCannon
## Passive income generator - produces coins over time, no attack

const COINS_PER_SECOND: float = 2.5
const COIN_TICK_INTERVAL: float = 0.4  # Generate coins every 0.4 seconds

var coin_timer: float = 0.0
var coins_accumulated: float = 0.0

func _ready() -> void:
	cannon_type = GameManager.CannonType.MINER
	cannon_name = "Miner"
	base_cost = 150
	max_hp = 150.0
	attack_range = 0.0  # No attack
	fire_rate = 0.0
	damage = 0.0
	crit_chance = 0.0

	super._ready()

	# Disable attack-related processing
	target = null


func _process(delta: float) -> void:
	if not is_active:
		return

	if not Settings.enable_miner_cannon:
		return

	# Generate coins over time
	coin_timer += delta
	coins_accumulated += COINS_PER_SECOND * _get_upgrade_multiplier() * delta

	if coin_timer >= COIN_TICK_INTERVAL:
		coin_timer = 0.0

		# Award accumulated coins
		var coins_to_give = int(coins_accumulated)
		if coins_to_give > 0:
			coins_accumulated -= coins_to_give
			GameManager.earn_cash(coins_to_give)
			_show_coin_effect()


func _show_coin_effect() -> void:
	# Visual feedback for coin generation
	var label = Label.new()
	label.text = "+$"
	label.add_theme_color_override("font_color", Color(1.0, 0.84, 0.0))  # Gold
	label.position = Vector2(-10, -40)
	add_child(label)

	var tween = create_tween()
	tween.set_parallel(true)
	tween.tween_property(label, "position:y", label.position.y - 20, 0.5)
	tween.tween_property(label, "modulate:a", 0.0, 0.5)
	tween.chain().tween_callback(label.queue_free)


# Override attack functions to do nothing
func _find_target() -> void:
	pass


func _rotate_towards_target(_delta: float) -> void:
	pass


func _fire() -> void:
	pass


# Miner has higher sell value due to income potential
func get_sell_value() -> int:
	# Base refund plus partial value of future income
	return int(total_invested * Settings.sell_refund_percent * 1.2)
