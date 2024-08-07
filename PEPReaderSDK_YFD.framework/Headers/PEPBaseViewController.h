//
//  PEPBaseViewController.h
//  PDFReaderSDK
//
//  Created by 李沛倬 on 2018/3/8.
//  Copyright © 2018年 pep. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 网络请求加载状态
 
 - PEPRequestDataStatusNotStart: 未开始。默认
 - PEPRequestDataStatusLoading: 正在加载
 - PEPRequestDataStatusSucceeded: 加载成功
 - PEPRequestDataStatusFailed: 加载失败
 */
typedef NS_ENUM(NSUInteger, PEPRequestDataStatus) {
    PEPRequestDataStatusNotStart,
    PEPRequestDataStatusLoading,
    PEPRequestDataStatusSucceeded,
    PEPRequestDataStatusFailed,
};

/**
 语音评测，导航类型
 */
typedef NS_ENUM(NSUInteger, PRVoiceEvaluateNavigationType) {
    PRVoiceEvaluateNavigationType_Left, //返回按钮
    PRVoiceEvaluateNavigationType_LeftAndRight  //返回和右侧按钮
};

@interface PEPBaseViewController : UIViewController

/**是否需要显示带人教logo的titleView，默认为false*/
@property (nonatomic, assign) BOOL needsShowTitleView;

/**导航栏最下方的分割线*/
@property (nonatomic, weak, readonly) UIView *navigationBarSeparatorView;

@property (nonatomic, assign, readonly) UIEdgeInsets safeAreaInsets;


/**
 设置状态栏颜色: 如需改变页面的状态栏颜色，可通过该方法在viewWillAppear中设置，别忘记在viewWillDisappear中还原
 
 @param color 状态栏颜色
 */
- (void)setStatusBarBackgroundColor:(UIColor *)color;


// MARK: - NavigationBar

- (void)configNavigationBarStyle;


- (void)restoreNavigationBarStyle;



// MARK: - Loading

/**数据请求状态：需要子类实现*/
@property (nonatomic, assign) PEPRequestDataStatus requestDataStatus;

@property (nonatomic, strong) UIView *loadingView;

@property (nonatomic, strong) UIView *animationLoadingView;

/**
 请求数据方法：基类不做具体实现，建议每个子类需要请求数据时分别实现该方法，以便别处可通过基类调用该方法以刷新数据和页面
 */
- (void)requestData;

- (void)showLoadingView;

/** progress: 0 ~ 1 */
- (void)showLoadingViewProgress:(CGFloat)progress speed:(NSString*)speedStr;

- (void)showLoadingViewWithTitle:(NSString *)title;

- (void)showAnimationLoadingViewProgress:(CGFloat)progress;
- (void)hideAnimationLoadingView;

- (void)hideLoadingView;



// MARK: - Alert

- (void)showAlertWithMessage:(NSString *)message
             sureButtonTitle:(NSString *)sureTitle
           cancelButtonTitle:(NSString *)cancelTitle
                  sureHandle:(void (^)(void))sureHandle
                cancelHandle:(void (^)(void))cancelHandle;

- (void)showAlertWithMessage:(NSString *)message sureHandle:(void (^)(void))sureHandle;

- (void)showActionSheetWithSourceView:(UIView *)sourceView
                                title:(NSString *)title
                         message:(NSString *)message
                     cancelTitle:(NSString *)cancelActionTitle
                firstActionTitle:(NSString *)firstActionTitle
               secondActionTitle:(NSString *)secondActionTitle
               firstActionHandle:(void (^)(void))firstActionHandle
              secondActionHandle:(void (^)(void))secondActionHandle;


// MARK: - Cover View

@property (nonatomic, strong) UIVisualEffectView *coverView;

@property (nonatomic, strong) UIVisualEffectView *blackCoverView;

@property (nonatomic, copy) void(^coverViewClicked)(void);
@property (nonatomic, copy) void(^blackCoverViewClicked)(void);
- (void)showCoverView;
- (void)showBlockCoverView;
-(void)hideBlackCoverView;

- (void)hideCoverView;




// MARK: - Network Error

@property (nonatomic, strong) UIButton *networkErrorView;

@property (nonatomic, copy) void(^networkErrorViewClicked)(void);

- (void)showNetworkErrorView;

- (void)hideNetworkErrorView;

// MARK: - CustomNavigation 语音测评 导航

- (void)loadCustomNavigationViewWithType:(PRVoiceEvaluateNavigationType)type;

/**
 语音测评-导航条自定义返回按钮设置返回图片 图片大小24*24  / 36*36 如果设置自定义图片，此方法在loadCustomNavigationViewWithType方法之前调用
 */

- (void)configNavigationCustomBackButtonWithImage:(UIImage *)image;

@end










