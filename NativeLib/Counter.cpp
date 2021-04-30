#include "Counter.h"

void Counter::_register_methods()
{
	register_method("_ready", &Counter::_ready);
}

void Counter::_init()
{
}

void Counter::_ready()
{
	value = Node::cast_to<Label>(get_node("Value"));
}

void Counter::SetValue(String str)
{
	value->set_text(str);
}
