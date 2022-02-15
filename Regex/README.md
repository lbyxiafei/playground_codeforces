[toc]
## 实用例子
### 提取固定pattern并替换部分
- 前后对比
    - Before: `ConfigurationManager.AppSettings["ClientId"]`
    - After: `Environment.GetEnvironmentVariable("ClientId", EnvironmentVariableTarget.Process)`
- 具体操作
    - Find: `ConfigurationManager.AppSettings\["(.*)"\]`
    - Replace: `Environment.GetEnvironmentVariable("$1", EnvironmentVariableTarget.Process)`