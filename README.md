# CJKCodec
将简体中文、英文混合的文本段落，利用文本格式的加密密钥，加密为由CJK基本字符集，CJK扩展字符集A所构成的文本段落。

例如，将上面这段文本使用密钥"人民利益高于一切"进行加密，得到下面的结果：

煊吘輟免緫䘹班毇襻蓐檠滧藐龝筹䀬班婀忣盌贠餷琀敠菊餎镁㶌緄鰮凶踱㪷㢒㙧琚颐倏蔢搖䂐㛋㒦㩋騍坍殓亶羚㔉疜逤丄瞼簃鋬嫉袕䡎


# C语言版本
包括encoder.c与decoder.c两个源码文件，使用gcc进行编译:

`gcc encoder.c -o encoder.exe`

`gcc decoder.c -o decoder.exe`

打开控制台，使用chcp 65001命令将编码改为UTF-8。

运行`encoder.exe`/`decoder.exe`，按照提示输入待加密/解密文本，密钥，得到结果。



