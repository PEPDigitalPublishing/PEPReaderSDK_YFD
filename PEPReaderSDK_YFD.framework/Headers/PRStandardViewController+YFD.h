//
//  PRStandardViewController+YFD.h
//  PDFReaderSDK
//
//  Created by 韩帅 on 2021/8/10.
//  Copyright © 2021 pep. All rights reserved.
//

#import "PRStandardViewController.h"

@interface PRStandardViewController (YFD)
/**
 08-10-2023更新日志
 getEvaluateViewControllerWithBookModel接口: 1.返回的评测控制器更替为新控制器
                                    2.返回的评测数据增加新数据
 
 08-25-2023更新日志
 新增评测列表页-购买弹窗提示通知 KPREVALUATE_NOACCESS
 */
/**
 跳转页码计算方式(最小为0)
 1.跳到常规页
 pageIndex =  书页上的页码 - ex_pages + titlePages
 2.跳到扉页(正式页码前的页,大多带有S标志,例如 S2)
 pageIndex =  书页上的页码
 
 if (书页上的页码 < self.bookModel.titlePages) {
    return 书页上的页码;
 } else {
    return 书页上的页码 - ex_pages + titlePages;
 }
 */

/// 常规初始化方法
/// @param bookID 教材ID
/// @param pageIndex 需要跳转的页码,页码计算详见上方注释(仅限已购买情况下,未购买情况下设置无效)
/// @param purchase 是否已购买：YES为已购买，阅读无限制；false为体验模式，仅可阅读前5页。默认为NO
+ (instancetype)openWithBookID:(NSString *)bookID pageIndex:(NSInteger)pageIndex purchase:(BOOL)purchase;


/// 临时体验初始化方法     (仅有一次体验机会,跳转页面后无法翻页)
/// @param bookID 教材ID
/// @param type 播放类型  此方法仅支持两种模式 PRYFDPlayingTypeClick: 点读 | PRYFDPlayingTypeContinue: 连读
/// @param pageIndex 需要跳转的页码,页码从0开始,页码计算详见上方注释(
/// @param resID  锚点资源id,播放类型为点读时需要传入,为空仅打开PDF 例:(英语新起点一年级上)resid= 12120011011230300001529562293446  跳转页码11
+ (instancetype)tempExperienceWithBookID:(NSString *)bookID readType:(PRYFDPlayingType)type pageIndex:(NSInteger)pageIndex resID:(NSString*)resID;

/// 已购买,跳页点读 初始化方法(内部校验购买权限,未购买跳转到第0页)
/// @param bookID 教材ID
/// @param type 播放类型  此方法仅支持两种模式 PRYFDPlayingTypeClick: 点读 | PRYFDPlayingTypeContinue: 连读
/// @param pageIndex 需要跳转的页码,页码从0开始,页码计算详见上方注释(
/// @param resID  锚点资源id,播放类型为点读时需要传入,为空仅打开PDF 例:(英语新起点一年级上)resid= 12120011011230300001529562293446  跳转页码11
+ (instancetype)jumpToReadingWithBookID:(NSString *)bookID readType:(PRYFDPlayingType)type pageIndex:(NSInteger)pageIndex resID:(NSString*)resID;


typedef void(^PREvaluateViewBackBlock) (UIViewController *evaluateVC,NSError *error);
/// 根据页码获取评测控制器    (需要请求网络数据,可适当展示loading)
/// @param bookModel bookModel
/// @param pageIndex 需要跳转的页码,页码计算详见上方注释(
/// @param block 结果回调
/// @param evaluateVC 返回评测控制器或者评测选择列表(控制器名称PRVoiceEvaluateViewController | PREvaluateListController,删除导航栈中控制器用)
/// @param error 返回错误信息 101-bookModel.bookID为空  102-无网络 103-当前页没有可评测内容  104-评测数据获取失败，请重试
+ (void)getEvaluateViewControllerWithBookModel:(PRBookModel*)bookModel pageIndex:(NSUInteger)pageIndex backBlock:(PREvaluateViewBackBlock)block;

/**
 ★★★评测列表中点击非免费内容通知--- 对接方需要自己定制体验模式结束、引导用户购买的弹窗
 通知名称  KPREVALUATE_NOACCESS
 返回评测列表控制器(NSDictionary形式)  notification.userInfo
 {@"viewcontroller": <PREvaluateListController>, @"bookModel": <PRBookModel>}
 */
/**
 ★★★评测结果用通知形式发送(样式如下)
 通知名称  KPREVALUATERESULT_YFD
 评测结果(NSDictionary形式)  notification.userInfo
 */

/**
 录音缓存地址  Documents/RJReadSDK/Record
 目录结构如下
 182a1ff9df646b20fa9fbbd52fb8659a.mp3    aa1dfd8b5c1f52e8873aa7a805852d76.mp3
 1896feec284dbce5910c83232339e150.mp3    f124ec0665ed96c95efe8bac172a87b4.mp3
 77402554ec1a2f1290963cc43474ba63.mp3    user+userI文件夹(评测数据)
 */

/**评测结果结果
 book_id
 sentences                   chapter_id    句子所属章节ID
                 durations     每次播放时长列表[]
                 end_date      句子内容在音频文件中的结束时间
                 file_path       原文音频路径
                 g_id              测评句子所属测评组的ID：每一个对话场景或一篇课文为一个测评组
                 jump_page   句子所属页码
                 name            测评组名
                 recordPath    录音路径
                 score             百分制分数
                 str_date        句子内容在音频文件中的开始时间
                 s_id               句子ID
                 text                句子内容
                 words              评测语句结果组  score 百分制分数
                                        type  类型 0:正确，16: 未发音，32: 重复发音，64: 回读，128: 替换
                                        word 单词或者汉字内容
                 08-10-2023 新增返回数据
                 integrity_score  完整度分
                 fluency_score   流畅度分
                 accuracy_score  准确度分 只有英文有准确度
                 phone_score    声韵分 中文用此字段代替准确度分 指声母和韵母正确率的得分
                 tone_score       调型分 指声调正确率的得分
 
 
 */
/** json串
 {
   "book_id" : "1212001101123",
   "sentences" : [
     {
       "file_path" : "\/pub_cloud\/23\/1212001101123\/121200110112320180731143036122.mp3",
       "score" : 100,
       "s_id" : "12120011011230100001529562293400_1",
       "end_date" : 4.8300000000000001,
       "recordPath" : "\/var\/mobile\/Containers\/Data\/Application\/B9952E7B-7B8D-4E1C-A902-B1ECC0A23200\/Documents\/RJReadSDK\/Record\/182a1ff9df646b20fa9fbbd52fb8659a.mp3",
       "chapter_id" : "1212001101123010000",
       "g_id" : "1212001101123010000_1",
       "words" : [
         {
           "score" : 100,
           "word" : "good",
           "type" : "0"
         },
         {
           "score" : 99.953804016113281,
           "word" : "morning",
           "type" : "0"
         },
         {
           "score" : 97.613143920898438,
           "word" : "i'm",
           "type" : "0"
         },
         {
           "score" : 96.765457153320312,
           "word" : "miss",
           "type" : "0"
         },
         {
           "score" : 81.2705078125,
           "word" : "wu",
           "type" : "0"
         },
         {
           "score" : 99.897262573242188,
           "word" : "what's",
           "type" : "0"
         },
         {
           "score" : 99.893577575683594,
           "word" : "your",
           "type" : "0"
         },
         {
           "score" : 95.98583984375,
           "word" : "name",
           "type" : "0"
         }
       ],
       "text" : "Good morning! I’m Miss Wu. What’s your name?",
       "jump_page" : 0,
       "durations" : [
         4.8300000000000001
       ],
       "name" : "Starter 主情境",
       "str_date" : 0
     },
     {
       "file_path" : "\/pub_cloud\/23\/1212001101123\/121200110112320180731143036542.mp3",
       "score" : 85,
       "s_id" : "12120011011230100001529562293401_1",
       "end_date" : 2.5600000000000001,
       "recordPath" : "\/var\/mobile\/Containers\/Data\/Application\/B9952E7B-7B8D-4E1C-A902-B1ECC0A23200\/Documents\/RJReadSDK\/Record\/77402554ec1a2f1290963cc43474ba63.mp3",
       "chapter_id" : "1212001101123010000",
       "g_id" : "1212001101123010000_1",
       "words" : [
         {
           "score" : 91.564193725585938,
           "word" : "hello",
           "type" : "0"
         },
         {
           "score" : 59.248241424560547,
           "word" : "my",
           "type" : "0"
         },
         {
           "score" : 92.586219787597656,
           "word" : "name",
           "type" : "0"
         },
         {
           "score" : 81.48748779296875,
           "word" : "is",
           "type" : "0"
         },
         {
           "score" : 70.799644470214844,
           "word" : "bill",
           "type" : "0"
         }
       ],
       "text" : "Hello! My name is Bill.",
       "jump_page" : 0,
       "durations" : [
         2.5600000000000001
       ],
       "name" : "Starter 主情境",
       "str_date" : 0
     },
     {
       "file_path" : "\/pub_cloud\/23\/1212001101123\/121200110112320180731143037066.mp3",
       "score" : 94,
       "s_id" : "12120011011230100001529562293402_1",
       "end_date" : 2.7999999999999998,
       "recordPath" : "\/var\/mobile\/Containers\/Data\/Application\/B9952E7B-7B8D-4E1C-A902-B1ECC0A23200\/Documents\/RJReadSDK\/Record\/f124ec0665ed96c95efe8bac172a87b4.mp3",
       "chapter_id" : "1212001101123010000",
       "g_id" : "1212001101123010000_1",
       "words" : [
         {
           "score" : 79.708999633789062,
           "word" : "good",
           "type" : "0"
         },
         {
           "score" : 66.747123718261719,
           "word" : "afternoon",
           "type" : "0"
         },
         {
           "score" : 99.857017517089844,
           "word" : "miss",
           "type" : "0"
         },
         {
           "score" : 68.662498474121094,
           "word" : "wu",
           "type" : "0"
         }
       ],
       "text" : "Good afternoon, Miss Wu.",
       "jump_page" : 1,
       "durations" : [
         2.7999999999999998
       ],
       "name" : "Starter 主情境",
       "str_date" : 0
     },
     {
       "file_path" : "\/pub_cloud\/23\/1212001101123\/121200110112320180731143037574.mp3",
       "score" : 96,
       "s_id" : "12120011011230100001529562293403_1",
       "end_date" : 1.54,
       "recordPath" : "\/var\/mobile\/Containers\/Data\/Application\/B9952E7B-7B8D-4E1C-A902-B1ECC0A23200\/Documents\/RJReadSDK\/Record\/aa1dfd8b5c1f52e8873aa7a805852d76.mp3",
       "chapter_id" : "1212001101123010000",
       "g_id" : "1212001101123010000_1",
       "words" : [
         {
           "score" : 98.390281677246094,
           "word" : "hi",
           "type" : "0"
         },
         {
           "score" : 98.683540344238281,
           "word" : "bill",
           "type" : "0"
         }
       ],
       "text" : "Hi, Bill.",
       "jump_page" : 1,
       "durations" : [
         1.54
       ],
       "name" : "Starter 主情境",
       "str_date" : 0
     },
     {
       "file_path" : "\/pub_cloud\/23\/1212001101123\/121200110112320180731143038035.mp3",
       "score" : 99,
       "s_id" : "12120011011230100001529562293404_1",
       "end_date" : 1.3100000000000001,
       "recordPath" : "\/var\/mobile\/Containers\/Data\/Application\/B9952E7B-7B8D-4E1C-A902-B1ECC0A23200\/Documents\/RJReadSDK\/Record\/7b5781d9b5a34f3b92d07c235c8f7f5a.mp3",
       "chapter_id" : "1212001101123010000",
       "g_id" : "1212001101123010000_1",
       "words" : [
         {
           "score" : 100,
           "word" : "bye",
           "type" : "0"
         },
         {
           "score" : 98.746795654296875,
           "word" : "bill",
           "type" : "0"
         }
       ],
       "text" : "Bye, Bill.",
       "jump_page" : 1,
       "durations" : [
         1.3100000000000001
       ],
       "name" : "Starter 主情境",
       "str_date" : 0
     },
     {
       "file_path" : "\/pub_cloud\/23\/1212001101123\/121200110112320180731143038448.mp3",
       "score" : 97,
       "s_id" : "12120011011230100001529562293405_1",
       "end_date" : 1.23,
       "recordPath" : "\/var\/mobile\/Containers\/Data\/Application\/B9952E7B-7B8D-4E1C-A902-B1ECC0A23200\/Documents\/RJReadSDK\/Record\/d5145be3ba9a2cdccd3fa4d941f992b4.mp3",
       "chapter_id" : "1212001101123010000",
       "g_id" : "1212001101123010000_1",
       "words" : [
         {
           "score" : 84.43402099609375,
           "word" : "goodbye",
           "type" : "0"
         }
       ],
       "text" : "Goodbye.",
       "jump_page" : 1,
       "durations" : [
         1.23
       ],
       "name" : "Starter 主情境",
       "str_date" : 0
     }
   ]
 }

 */
@end


