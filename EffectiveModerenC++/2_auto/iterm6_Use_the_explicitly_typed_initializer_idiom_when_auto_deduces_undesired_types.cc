// 注意auto有时候推导的并不是你想象的（原因是你不熟）
// 所以可以强制初始化

e.g.

vector<bool> vec;

auto x = vec[5]; // 并不是bool，而是一个代理类
auto x = static_cast<bool>(vec[5]); 会更好
