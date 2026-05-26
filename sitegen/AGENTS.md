## Development Rules

### General Rules

#### Coding Style
- 使用 `ruff format` 排版代码
- 使用 `__foo` 风格的 private 变量和方法
- 总是使用 type annotations
- 使用 @utils/logger.py 维护日志

#### Code Quality
- 使用 `ruff check --fix` 维持基本代码质量
- 避免循环或条件分支的深层嵌套，累计不得超过三层
- 避免单个过大函数

#### System Maintenance (IMPORTANT)
- 权衡代码实现的抽象层级，避免紧耦合，避免过度模块化
- 采取 API 优先的设计原则，任何组件/模块的对外接口必须清晰简单

#### Type Annotations
- 对内置类型使用 `list`, `dict`... 而不是 `List`, `Dict`...
- 非必要不使用 `Any` 和 `cast`
- 在遇到难以处理的三方库类型问题时，使用 typedef 拆解隔离问题，避免类型污染
- 未经确认不得使用 @type-ignore 注解

#### Imports
- 总是将 import 语句放在文件顶部
- 根据来源和用途组织 import 语句：内部导入在最前面，然后是标准库，最后是第三方库；内部导入和库导入分成两组，之间用空行分割
- 使用完整路径编写内部导入，例如 `from foo.bar import *`
- 不要导入 `__future__` 模块如 `annotation` 等

#### Logging
- 总是使用子系统对应的 logging 模块添加日志记录，而不是 naive print
- 总是将 log 同时输出到控制台和 tmp/logs/{module}.log
- 通过 info-level logging 暴露模块状态变迁和业务逻辑执行
- 通过 debug-level logging 暴露细节执行状态

#### Error Handling
- 不要过度使用 try-except 吞噬 exception ，优先考虑是否将其暴露以避免对开发者透明
- 总是在 throw exception 之前 log 相关对象的状态

#### Comments
- 使用英文编写注释
- 总是为分隔的代码段编写一行简洁的注释说明其功能用途；对于此类行内注释，开头字母不要大写，不要在结尾加句号
- 总是为方法编写 docstring ，除非有抽象基类已编写，且继承者的功能完全相同；遵循正常英文写作语法，也就是说，要有首字母大写与结尾句号
- docstring 遵循如下格式：
```py
def foo(x: int, y: str) -> bool:
   """aaa bbb xxx ccccc...
      foo bar...
      - x: blabla
      - y: blabla
      return: blabla
   """
   code...
```

### Task-Specific Rules

#### Bug Fixing
- First understand, then fix
- Analyze root cause
- Write regression test for non-trivial cases

#### Refactoring
- 确保代码原有功能和语义不变
