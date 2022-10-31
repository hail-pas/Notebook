## Design Model
> 代码解藕； 使其易重构改变（对象、代码块之间的依赖降低）
> 变化 以及 应付变化
> 类间关系：组合-动态 > 继承-静态
> 抽象  - 具体
----
## Strategy   --策略模式，将变化的部分提取、封装、调用组合
```python
class Strategy(object):
  	# 基本属性
    variable = ChangePart().behavior()  # 内部封装抽象的变化行为，实例化时具体实现
    # 或者使用抽象方法，子类自己实现
    def behavior(self):
        # abstract
        raise NotImplementedError("Duck: NotImplemented!")
```

----
## Singleton   --单例模式，永远使用同一个实例

> 管理共享资源
> threading.Lock()  同步互斥锁

```python
def synchronizd(func):
  	@funtools.wraps(func)
    def wrapper(cls, *args, **kwargs):
      	with cls.__lock:
          	return func(cls, *args, **kwargs)

class Singleton(object):

		__instance = None   # 直接创建 Singleton
    __lock = threading.Lock()
    
    @synchronizd
		@classmethod	   #直接类名调用
		def get_instance(cls): 
				if not cls.__instance:
          	with self.__lock:
								cls.__instance = Singleton()
				return cls.__instance

- 使用    -- 只需要固定数量的接口，节省内存；数据库链接池、socket固定链接
	- Singleton.get_instance()    --类调用
- 保证
	- 同步互斥锁 threading.Lock()
	- 事先创建唯一实例
  - 双重检查加锁 # 只在为创建之前加锁
```

## Observer   --观察者模式
> subject - observer （对象之间的一对多关系：主题对象 <--依赖者对象）
> 		注册订阅 - 接收 - 取消订阅
> Django的信号
```python
class Subject(object):
    def __init__(self, **kwargs):
        super().__init__()
        self.sub = "SUBJECT"
        self.initialize(**kwargs)
        
    # 属性扩展
    def _initialize(self, **kwargs) -> None:
        for key, value in kwargs.items():
            setattr(self, key, value)

    initialize = _initialize

    def register_observer(self, observer):
        raise NotImplementedError
        
    def delete_observer(self, *args, **kwargs):
        raise NotImplementedError

    def notify(self, *args, **kwargs):
        raise NotImplementedError


class Observer(object):
    def update(self, *args, **kwargs):
        raise NotImplementedError


class Display(object):
    def display(self, *args, **kwargs):
        raise NotImplementedError


class WeatherData(Subject):
    _observer_list = []
    _kwargs = {"temperature": None, "humidity": None, "pressure": None}

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

    def register_observer(self, observer):
        if observer not in self._observer_list:
            self._observer_list.append(observer)

    def delete_observer(self, observer):
        if observer in self._observer_list:
            return self._observer_list.remove(observer)

    def notify(self):
        for observer in self._observer_list:
            observer.update(**self._kwargs)

    def measurements_changed(self):
        self.notify()

    def set_measurements(self, *args):
        for key, value in zip(self._kwargs.keys(), args):
            self._kwargs[key] = value
        self.measurements_changed()


class CurrentConditionDisplay(Observer, Display):
    _kwargs = {}

    def __init__(self, weather_data):
        self.weather_data = weather_data

    def update(self, **kwargs):
        self._kwargs = kwargs
        self.display()

    def display(self):
        print("=" * 10 + "Current Condition Display" + "=" * 10)
        for key, value in self._kwargs.items():
            print(" " * 4 + f"{key}: {value}")


kwargs = {
    "name": "phoenix",
    "age": 24,
    "gender": "male"
}
observer1 = CurrentConditionDisplay("Weather Data")
observer2 = CurrentConditionDisplay("Weather Data")
wd = WeatherData(**kwargs)  # 属性扩展
wd.register_observer(observer1)
wd.register_observer(observer2)
args = [80, 65, "30.4f"]
wd.set_measurements(*args)   # 主题更新，自动发布，多次更新触发
# 流程
注册：register_observer(observer1)  # 关注者列表 + 变量名集合
发布：set_measurements(*args) -> measurements_changed -> notify() -> Obs
观察者触发：update(**self._kwargs) -> display()
```
## 装饰者模式

> 装饰者(子类-「抽象-具体」) 需要能够替代 被装饰者(超类-抽象)
> 行为来自装饰者间的嵌套传递 （ java - 组合 ）
> 动态的获取新行为，继承是在定义是静态的赋予

```python
# 将被装饰的对象实例作为 init参数 传入
class TextTag(object):
    """Represents a base text tag"""

    def __init__(self, text):
        self._text = text

    def render(self):
        return self._text


class BoldWrapper(TextTag):
    """Wraps a tag in <b>"""

    def __init__(self, wrapped):
        self._wrapped = wrapped
        super().__init__(self._wrapped.render())

    def render(self):
        return "<b>{}</b>".format(self._wrapped.render())


class ItalicWrapper(TextTag):
    """Wraps a tag in <i>"""

    def __init__(self, wrapped):
        self._wrapped = wrapped
        super().__init__(self._wrapped.render())

    def render(self):
        return "<i>{}</i>".format(self._wrapped.render())

base_text = TextTag("hello, world!")
bold_text = BoldWrapper(base_text)   # render()展示
italic_bold_text = ItalicWrapper(BoldWrapper(base_text)) # render()展示
```

## 工厂模式

>行为是创建新对象的类
>抽象类1 - n具体类

```python
# 工厂类 - 工厂方法
# 简单工厂方法 simple-factory
class GreekLocalizer(object):

class EnglishLocalizer(object):
  
def get_localizer(language="English"): # 可调用对象传递
    """Factory"""
    localizers = { # 参数 - 类 映射表
        "English": EnglishLocalizer,
        "Greek": GreekLocalizer,
    }
    return localizers[language]()
# 抽象工厂模式 abstract-factory
class AbstractFactory(object):
  	_instance = None
    self._name_inventory = {}
  	def __init__(self, instance_name):
      	self.prepare(instance_name)
        return self._name_inventory[instance_name]()
    def prepare(instance_name):
      	pass
   	def register(self, cls): # 初始化
      	self._name_inventory[cls.__name__] = cls
    def unregister(self, cls):
      	if cls.__name__ in self._name_inventory.keys():
          	return self._name_inventory.pop(cls.__name__) # del self._name_inventory[cls.__name__]

```

## 命令模式

> 接收者和动作 打包 （队列请求）
> 行为来自装饰者间的嵌套传递 （ java - 组合 ）
> 动态的获取新行为，继承是在定义、静态的赋予

```python
# 抽象命令 - 接收对象 > 具体命令 -- 调用者（设置、动作触发）
class Command(object):  # 抽象命令
    def execute(self):
        raise NotImplementedError
        

class Light(object):  # 接收对象
    status = False

    def swith(self):
        if self.status:
            self.status = False
        else:
            self.status = True

    def show_status(self):
        print("====status:", self.status)


class LightCommand(Command): # 具体命令
    def __init__(self, light):
        self.light = light

    def execute(self):
        self.light.swith()


class Client(object): # 调用者
    command = None

    def set_command(self, command):
        print("====set command")
        self.command = command

    def action(self):
        print("====execute command")
        self.command.execute()
cli = Client()
light_cmd = LightCommand(Light())
cli.set_command(light_cmd)
cli.action()
```

## 适配器模式与外观模式

> 适配器模式
> 	中间耦合件、状态转换
> 	用户  --> [规范化]适配器[封装修改] --> 接口
> 外观模式
> 	让多接口调用更简单、统一封装整合 -> 高级接口
> 	最少知识原则
```python
class Adaptor():
  	def __init__(self, s):
      	pass
    def method(self, ):
      	pass
```

## 模板方法模式

> 类中的方法 抽象定义骨架、流程，具体实现留给子类; 控制算法

```python
class BaseModel(object):
  	def __skeleton__(self, init)
    		self.func1()
      	self.func2()
        self.func3()
        self.hook()
    def func1(self):
      	raise NotImplementedError
    def hook(self):
      	return True
class Subordinate(BaseModel):
  	def func1(self):
      	pass
    def hook(self):
      	pass
```

## 状态模式

> 状态图 --> 状态迁移（动作）
> 类状态机 - 方法动作 - 属性状态  ===>  单个状态类（属性状态、方法动作）==> 组合成状态机类




































