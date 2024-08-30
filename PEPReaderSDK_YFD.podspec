

Pod::Spec.new do |s|

  s.name         = 'PEPReaderSDK_YFD'

  s.version      = '2.8.18'

  s.summary      = '人教点读新SDK'

  s.author       = { 'PEP' => '' }

  s.platform     =  :ios, '11.0'

  s.homepage     = 'https://github.com/PEPDigitalPublishing/PEPReaderSDK_YFD'

  s.source       = { :git => 'https://github.com/PEPDigitalPublishing/PEPReaderSDK_YFD.git'}

  s.vendored_frameworks = 'PEPReaderSDK_YFD.framework'

  s.resources = ['PDFReaderSDKDiandu.xcassets', 'PEPReaderSDK_YFD.framework/PEPPDFReaderSDK.bundle']

  s.frameworks   = 'MobileCoreServices', 'Security', 'CoreTelephony', 'AudioToolbox', 'CoreGraphics', 'QuartzCore', 'SystemConfiguration', 'AddressBook', 'CoreLocation', 'Contacts'

  s.ios.library = 'z', 'c++'

  s.dependency 'YYModel'
  s.dependency 'Masonry'
  s.dependency 'SAMKeychain'
  s.dependency 'SSZipArchive'
  s.dependency 'iosMath'
  
  s.dependency 'MZTimerLabel'
  s.dependency 'PEPBigData', '>= 0.4.4'
  s.dependency 'PEPNetworking', '>= 0.4.1'
  
  s.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }

  s.requires_arc = true

end



















