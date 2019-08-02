# Halcon 学习笔记

###学习案例

* examples\quick guide\hdevelop\surface scratch.dev<br>
由區域的二值化和形態學來檢查平面上的刮痕 --->在Quick Guide有詳細的介紹 <br><br>
* examples\application guide\shape matching\hdevelop\ first example shape matching.dev <br>
介紹HALCON型狀導向的匹配 --->在Application Note on Shape-Based Matching有詳細的描述 <br><br>
* examples\application guide\shape matching\hdevelop\process shape model.dev<br>
經由更改顯示型狀模型的結果產生另一個ROI的模型 --->在Application Note on Shape-Based Matching有詳細的描述 <br><br>
* examples\hdevelop\Morphology\Gray-Values\pcb inspection.dev <br>
使用灰階值型態學在PCB上找尋缺陷 <br><br>


###简单语法
x = y + z;<br>
以 C 的語法是 assign(y + z,x)<br>
在程式視窗中就會顯示成  x := y + z<br>
 
###OS操作
'file',  ---指定搜索的格式为文件<br>
'directories',  ---指定搜索的格式为文件夹<br>
'recursive' ---指定可以遍历子文件夹里面的文件<br>
'follow_links', ---<br>
'max_depth 5', ---指定遍历的深度<br>
'max_file 1000', ---指定遍历的最大文件数<br>
'ignore_case', ---忽略大小写<br>
'\\.(tif|tiff|gif|bmp|jpg|jpeg|jp2|png|pcx|pgm|ppm|pbm|xwd|ima|hobj)$', --- 图片类型<br>