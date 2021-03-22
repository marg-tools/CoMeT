TUNE=base
EXT=sniper-x86_64-gcc43
NUMBER=483
NAME=xalancbmk
SOURCES= AIXPlatformUtils.cpp CSetDefs.cpp BinHTTPURLInputStream.cpp \
	 Win32PlatformUtils.cpp Win32MsgLoader.cpp Win32TransService.cpp \
	 Win32TransService2.cpp WinSockNetAccessor.cpp SunCCDefs.cpp \
	 SolarisPlatformUtils.cpp GCCDefs.cpp LinuxPlatformUtils.cpp \
	 MIPSproDefs.cpp IRIXPlatformUtils.cpp HPCCDefs.cpp HPPlatformUtils.cpp \
	 WFXMLScanner.cpp ASCIIRangeFactory.cpp AbstractDOMParser.cpp \
	 AbstractNumericFacetValidator.cpp AbstractNumericValidator.cpp \
	 AbstractStringValidator.cpp AllContentModel.cpp \
	 AnySimpleTypeDatatypeValidator.cpp AnyURIDatatypeValidator.cpp \
	 AttrImpl.cpp AttrMapImpl.cpp AttrNSImpl.cpp BMPattern.cpp Base64.cpp \
	 Base64BinaryDatatypeValidator.cpp BinFileInputStream.cpp \
	 BinFileOutputStream.cpp BinInputStream.cpp BinMemInputStream.cpp \
	 BinMemOutputStream.cpp BinOutputStream.cpp BitSet.cpp \
	 BlockRangeFactory.cpp BooleanDatatypeValidator.cpp CDATASectionImpl.cpp \
	 CMAny.cpp CMBinaryOp.cpp CMUnaryOp.cpp CharToken.cpp \
	 CharacterDataImpl.cpp ChildNode.cpp ClosureToken.cpp CommentImpl.cpp \
	 ComplexTypeInfo.cpp ConcatToken.cpp ConditionToken.cpp \
	 ContentLeafNameTypeVector.cpp ContentSpecNode.cpp DFAContentModel.cpp \
	 DGXMLScanner.cpp DOMAttrImpl.cpp DOMAttrMapImpl.cpp DOMAttrNSImpl.cpp \
	 DOMBuilderImpl.cpp DOMCDATASectionImpl.cpp DOMCharacterDataImpl.cpp \
	 DOMChildNode.cpp DOMCommentImpl.cpp DOMConfigurationImpl.cpp \
	 DOMDeepNodeListImpl.cpp DOMDocumentFragmentImpl.cpp DOMDocumentImpl.cpp \
	 DOMDocumentTypeImpl.cpp DOMElementImpl.cpp DOMElementNSImpl.cpp \
	 DOMEntityImpl.cpp DOMEntityReferenceImpl.cpp DOMErrorImpl.cpp \
	 DOMException.cpp DOMImplementationImpl.cpp DOMImplementationRegistry.cpp \
	 DOMLocatorImpl.cpp DOMNamedNodeMapImpl.cpp DOMNodeIDMap.cpp \
	 DOMNodeImpl.cpp DOMNodeIteratorImpl.cpp DOMNodeListImpl.cpp \
	 DOMNodeVector.cpp DOMNormalizer.cpp DOMNotationImpl.cpp \
	 DOMParentNode.cpp DOMParser.cpp DOMProcessingInstructionImpl.cpp \
	 DOMRangeException.cpp DOMRangeImpl.cpp DOMString.cpp DOMStringPool.cpp \
	 DOMTextImpl.cpp DOMTreeWalkerImpl.cpp DOMTypeInfoImpl.cpp \
	 DOMWriterImpl.cpp DOMXPathException.cpp DOM_Attr.cpp \
	 DOM_CDATASection.cpp DOM_CharacterData.cpp DOM_Comment.cpp \
	 DOM_DOMException.cpp DOM_DOMImplementation.cpp DOM_Document.cpp \
	 DOM_DocumentFragment.cpp DOM_DocumentType.cpp DOM_Element.cpp \
	 DOM_Entity.cpp DOM_EntityReference.cpp DOM_NamedNodeMap.cpp DOM_Node.cpp \
	 DOM_NodeFilter.cpp DOM_NodeIterator.cpp DOM_NodeList.cpp \
	 DOM_Notation.cpp DOM_ProcessingInstruction.cpp DOM_Range.cpp \
	 DOM_RangeException.cpp DOM_Text.cpp DOM_TreeWalker.cpp DOM_XMLDecl.cpp \
	 DStringPool.cpp DTDAttDef.cpp DTDAttDefList.cpp DTDElementDecl.cpp \
	 DTDEntityDecl.cpp DTDGrammar.cpp DTDScanner.cpp DTDValidator.cpp \
	 DatatypeValidator.cpp DatatypeValidatorFactory.cpp \
	 DateDatatypeValidator.cpp DateTimeDatatypeValidator.cpp \
	 DateTimeValidator.cpp DayDatatypeValidator.cpp \
	 DecimalDatatypeValidator.cpp DeepNodeListImpl.cpp \
	 DefaultPanicHandler.cpp DocumentFragmentImpl.cpp DocumentImpl.cpp \
	 DocumentTypeImpl.cpp DomMemDebug.cpp DoubleDatatypeValidator.cpp \
	 Dummy.cpp DurationDatatypeValidator.cpp ENTITYDatatypeValidator.cpp \
	 ElemStack.cpp ElementDefinitionImpl.cpp ElementImpl.cpp \
	 ElementNSImpl.cpp EncodingValidator.cpp EntityImpl.cpp \
	 EntityReferenceImpl.cpp FieldActivator.cpp FieldValueMap.cpp \
	 FloatDatatypeValidator.cpp GeneralAttributeCheck.cpp Grammar.cpp \
	 GrammarResolver.cpp HashPtr.cpp HashXMLCh.cpp HeaderDummy.cpp HexBin.cpp \
	 HexBinaryDatatypeValidator.cpp IC_Field.cpp IC_Key.cpp IC_KeyRef.cpp \
	 IC_Selector.cpp IC_Unique.cpp IDDatatypeValidator.cpp \
	 IDREFDatatypeValidator.cpp IGXMLScanner.cpp IGXMLScanner2.cpp \
	 IconvTransService.cpp IdentityConstraint.cpp InMemMsgLoader.cpp \
	 InputSource.cpp KVStringPair.cpp ListDatatypeValidator.cpp \
	 LocalFileFormatTarget.cpp LocalFileInputSource.cpp Match.cpp \
	 MemBufFormatTarget.cpp MemBufInputSource.cpp MemoryManagerArrayImpl.cpp \
	 MemoryManagerImpl.cpp MixedContentModel.cpp ModifierToken.cpp \
	 MonthDatatypeValidator.cpp MonthDayDatatypeValidator.cpp Mutexes.cpp \
	 NCNameDatatypeValidator.cpp NOTATIONDatatypeValidator.cpp \
	 NameDatatypeValidator.cpp NamedNodeMapImpl.cpp NamespaceScope.cpp \
	 NodeIDMap.cpp NodeImpl.cpp NodeIteratorImpl.cpp NodeListImpl.cpp \
	 NodeVector.cpp NotationImpl.cpp Op.cpp OpFactory.cpp PSVIAttribute.cpp \
	 PSVIAttributeList.cpp PSVIElement.cpp PSVIItem.cpp PanicHandler.cpp \
	 ParenToken.cpp ParentNode.cpp ParserForXMLSchema.cpp PlatformUtils.cpp \
	 ProcessingInstructionImpl.cpp QName.cpp QNameDatatypeValidator.cpp \
	 RangeFactory.cpp RangeImpl.cpp RangeToken.cpp RangeTokenMap.cpp \
	 ReaderMgr.cpp RefCountedImpl.cpp RegularExpression.cpp RegxParser.cpp \
	 RegxUtil.cpp SAX2XMLReaderImpl.cpp SAXException.cpp \
	 SAXParseException.cpp SAXParser.cpp SGXMLScanner.cpp SchemaAttDef.cpp \
	 SchemaAttDefList.cpp SchemaElementDecl.cpp SchemaGrammar.cpp \
	 SchemaInfo.cpp SchemaSymbols.cpp SchemaValidator.cpp \
	 SimpleContentModel.cpp StdInInputSource.cpp StdOutFormatTarget.cpp \
	 StringDatatypeValidator.cpp StringPool.cpp StringToken.cpp \
	 SubstitutionGroupComparator.cpp SynchronizedStringPool.cpp TextImpl.cpp \
	 TimeDatatypeValidator.cpp Token.cpp TokenFactory.cpp TransService.cpp \
	 TraverseSchema.cpp TreeWalkerImpl.cpp URLInputSource.cpp \
	 UnicodeRangeFactory.cpp UnionDatatypeValidator.cpp UnionToken.cpp \
	 ValidationContextImpl.cpp ValueStore.cpp ValueStoreCache.cpp \
	 VecAttrListImpl.cpp VecAttributesImpl.cpp WFXMLScanner.cpp \
	 Wrapper4DOMInputSource.cpp Wrapper4InputSource.cpp \
	 XML256TableTranscoder.cpp XML88591Transcoder.cpp XMLASCIITranscoder.cpp \
	 XMLAbstractDoubleFloat.cpp XMLAttDef.cpp XMLAttDefList.cpp XMLAttr.cpp \
	 XMLBigDecimal.cpp XMLBigInteger.cpp XMLBuffer.cpp XMLBufferMgr.cpp \
	 XMLCanRepGroup.cpp XMLChTranscoder.cpp XMLChar.cpp XMLContentModel.cpp \
	 XMLDTDDescription.cpp XMLDTDDescriptionImpl.cpp XMLDateTime.cpp \
	 XMLDeclImpl.cpp XMLDouble.cpp XMLEBCDICTranscoder.cpp XMLElementDecl.cpp \
	 XMLEntityDecl.cpp XMLException.cpp XMLFloat.cpp XMLFormatter.cpp \
	 XMLGrammarDescription.cpp XMLGrammarPoolImpl.cpp \
	 XMLIBM1047Transcoder.cpp XMLIBM1140Transcoder.cpp XMLMsgLoader.cpp \
	 XMLNotationDecl.cpp XMLNumber.cpp XMLRangeFactory.cpp XMLReader.cpp \
	 XMLRecognizer.cpp XMLRefInfo.cpp XMLScanner.cpp XMLScannerResolver.cpp \
	 XMLSchemaDescription.cpp XMLSchemaDescriptionImpl.cpp XMLString.cpp \
	 XMLStringTokenizer.cpp XMLUCSTranscoder.cpp XMLURL.cpp \
	 XMLUTF16Transcoder.cpp XMLUTF8Transcoder.cpp XMLUni.cpp \
	 XMLUniCharacter.cpp XMLUri.cpp XMLValidator.cpp XMLWin1252Transcoder.cpp \
	 XMemory.cpp XObjectComparator.cpp XPathMatcher.cpp XPathMatcherStack.cpp \
	 XPathSymbols.cpp XProtoType.cpp XSAnnotation.cpp \
	 XSAttributeDeclaration.cpp XSAttributeGroupDefinition.cpp \
	 XSAttributeUse.cpp XSComplexTypeDefinition.cpp XSDDOMParser.cpp \
	 XSDElementNSImpl.cpp XSDErrorReporter.cpp XSDLocator.cpp \
	 XSElementDeclaration.cpp XSFacet.cpp XSIDCDefinition.cpp XSModel.cpp \
	 XSModelGroup.cpp XSModelGroupDefinition.cpp XSMultiValueFacet.cpp \
	 XSNamespaceItem.cpp XSNotationDeclaration.cpp XSObject.cpp \
	 XSObjectFactory.cpp XSParticle.cpp XSSimpleTypeDefinition.cpp \
	 XSTypeDefinition.cpp XSWildcard.cpp XSerializeEngine.cpp \
	 XTemplateComparator.cpp XTemplateSerializer.cpp XUtil.cpp \
	 XercesAttGroupInfo.cpp XercesDOMParser.cpp XercesElementWildcard.cpp \
	 XercesGroupInfo.cpp XercesXPath.cpp YearDatatypeValidator.cpp \
	 YearMonthDatatypeValidator.cpp sax2Dummy.cpp DOMServices.cpp \
	 DOMSupport.cpp DOMSupportDefault.cpp DOMSupportException.cpp \
	 DOMSupportInit.cpp TreeWalker.cpp XalanDocumentPrefixResolver.cpp \
	 XalanNamespacesStack.cpp AttributeListImpl.cpp AttributesImpl.cpp \
	 DOMStringHelper.cpp DOMStringPrintWriter.cpp DoubleSupport.cpp \
	 Writer.cpp ExecutionContext.cpp FormatterListener.cpp \
	 NamedNodeMapAttributeList.cpp NullPrintWriter.cpp \
	 PlatformSupportInit.cpp PrefixResolver.cpp PrintWriter.cpp \
	 Resettable.cpp StdBinInputStream.cpp StringTokenizer.cpp URISupport.cpp \
	 XSLException.cpp XalanBitmap.cpp XalanDOMStringCache.cpp \
	 XalanDOMStringAllocator.cpp XalanDOMStringHashTable.cpp \
	 XalanDOMStringPool.cpp XalanDecimalFormatSymbols.cpp \
	 XalanEncodingPropertyCache.cpp XalanFStreamOutputStream.cpp \
	 XalanFileOutputStream.cpp XalanICUMessageLoader.cpp \
	 XalanInMemoryMessageLoader.cpp XalanMessageLoader.cpp \
	 XalanNLSMessageLoader.cpp XalanNullOutputStream.cpp \
	 XalanNumberFormat.cpp XalanOutputStream.cpp \
	 XalanOutputStreamPrintWriter.cpp XalanParsedURI.cpp \
	 XalanReferenceCountedObject.cpp XalanSimplePrefixResolver.cpp \
	 XalanStdOutputStream.cpp XalanTranscodingServices.cpp \
	 XalanToXercesTranscoderWrapper.cpp XalanUTF16Transcoder.cpp \
	 XalanXMLChar.cpp NodeNameTreeWalker.cpp ICUResHandler.cpp \
	 InMemHandler.cpp MsgFileOutputStream.cpp NLSHandler.cpp SAX2Handler.cpp \
	 XalanMsgLib.cpp FormatterToDOM.cpp FormatterToHTML.cpp \
	 FormatterToNull.cpp FormatterToText.cpp FormatterToXML.cpp \
	 FormatterToXMLBase.cpp FormatterToXML_UTF16.cpp FormatterToXML_UTF8.cpp \
	 XMLSupportInit.cpp FormatterTreeWalker.cpp XMLParserLiaison.cpp \
	 XMLSupportException.cpp XalanHTMLElementsProperties.cpp \
	 ElementPrefixResolverProxy.cpp FormatterStringLengthCounter.cpp \
	 Function.cpp FunctionConcat.cpp FunctionContains.cpp FunctionID.cpp \
	 FunctionLang.cpp FunctionNamespaceURI.cpp FunctionNormalizeSpace.cpp \
	 FunctionStartsWith.cpp FunctionString.cpp FunctionSubstring.cpp \
	 FunctionSubstringAfter.cpp FunctionSubstringBefore.cpp \
	 FunctionTranslate.cpp MutableNodeRefList.cpp NodeRefList.cpp \
	 NodeRefListBase.cpp XBoolean.cpp XNodeSet.cpp XNodeSetAllocator.cpp \
	 XNodeSetBase.cpp XNodeSetNodeProxy.cpp XNodeSetNodeProxyAllocator.cpp \
	 XNodeSetResultTreeFragProxy.cpp XNull.cpp XNumber.cpp \
	 XNumberAllocator.cpp XNumberBase.cpp XObject.cpp XObjectFactory.cpp \
	 XObjectFactoryDefault.cpp XObjectResultTreeFragProxy.cpp \
	 XObjectResultTreeFragProxyBase.cpp XObjectResultTreeFragProxyText.cpp \
	 XObjectTypeCallback.cpp XPath.cpp XPathAllocator.cpp \
	 XPathConstructionContext.cpp XPathConstructionContextDefault.cpp \
	 XPathEnvSupport.cpp XPathEnvSupportDefault.cpp XPathEvaluator.cpp \
	 XPathExecutionContext.cpp XPathExecutionContextDefault.cpp \
	 XPathExpression.cpp XPathFactory.cpp XPathFactoryBlock.cpp \
	 XPathFactoryDefault.cpp XPathFunctionTable.cpp XPathInit.cpp \
	 XPathParserException.cpp XPathProcessor.cpp XPathProcessorImpl.cpp \
	 XSpan.cpp XString.cpp XStringAdapter.cpp XStringAdapterAllocator.cpp \
	 XStringAllocator.cpp XStringBase.cpp XStringCached.cpp \
	 XStringCachedAllocator.cpp XStringReference.cpp \
	 XStringReferenceAllocator.cpp XToken.cpp XTokenNumberAdapter.cpp \
	 XUnknown.cpp XTokenNumberAdapterAllocator.cpp XTokenStringAdapter.cpp \
	 XTokenStringAdapterAllocator.cpp \
	 XalanDocumentFragmentNodeRefListBaseProxy.cpp XalanQName.cpp \
	 XalanQNameByReference.cpp XalanQNameByValue.cpp \
	 XalanQNameByValueAllocator.cpp XalanXPathException.cpp XPathCAPI.cpp \
	 AVTPart.cpp AVT.cpp AVTPartSimple.cpp AVTPartXPath.cpp Constants.cpp \
	 CountersTable.cpp ElemApplyImport.cpp ElemApplyTemplates.cpp \
	 ElemAttribute.cpp ElemChoose.cpp ElemAttributeSet.cpp \
	 ElemCallTemplate.cpp ElemComment.cpp ElemCopy.cpp ElemCopyOf.cpp \
	 ElemDecimalFormat.cpp ElemElement.cpp ElemEmpty.cpp ElemFallback.cpp \
	 ElemExtensionCall.cpp ElemForEach.cpp ElemForwardCompatible.cpp \
	 ElemIf.cpp ElemLiteralResult.cpp ElemMessage.cpp ElemNumber.cpp \
	 ElemOtherwise.cpp ElemPI.cpp ElemParam.cpp ElemSort.cpp ElemTemplate.cpp \
	 ElemTemplateElement.cpp ElemText.cpp ElemTextLiteral.cpp ElemUse.cpp \
	 ElemValueOf.cpp ElemVariable.cpp ElemWhen.cpp ElemWithParam.cpp \
	 ExtensionFunctionHandler.cpp ExtensionNSHandler.cpp FunctionCurrent.cpp \
	 FunctionDocument.cpp FunctionElementAvailable.cpp \
	 FunctionFormatNumber.cpp FunctionFunctionAvailable.cpp \
	 FunctionGenerateID.cpp FunctionKey.cpp FunctionSystemProperty.cpp \
	 FunctionUnparsedEntityURI.cpp GenerateEvent.cpp KeyTable.cpp \
	 NamespacesHandler.cpp NodeSortKey.cpp NodeSorter.cpp \
	 OutputContextStack.cpp ProblemListener.cpp ProblemListenerDefault.cpp \
	 ResultNamespacesStack.cpp SelectionEvent.cpp Stylesheet.cpp \
	 StylesheetExecutionContext.cpp StylesheetConstructionContext.cpp \
	 StylesheetConstructionContextDefault.cpp \
	 StylesheetExecutionContextDefault.cpp StylesheetHandler.cpp \
	 StylesheetRoot.cpp TopLevelArg.cpp TraceListener.cpp \
	 TraceListenerDefault.cpp TracerEvent.cpp VariablesStack.cpp \
	 XResultTreeFrag.cpp XResultTreeFragAllocator.cpp XSLTEngineImpl.cpp \
	 XSLTInit.cpp XSLTInputSource.cpp XSLTProcessor.cpp \
	 XSLTProcessorEnvSupport.cpp XSLTProcessorEnvSupportDefault.cpp \
	 XSLTProcessorException.cpp XSLTResultTarget.cpp XalanAVTAllocator.cpp \
	 XalanAVTPartSimpleAllocator.cpp XalanAVTPartXPathAllocator.cpp \
	 XalanElemApplyTemplatesAllocator.cpp XalanElemAttributeAllocator.cpp \
	 XalanElemAttributeSetAllocator.cpp XalanElemCallTemplateAllocator.cpp \
	 XalanElemElementAllocator.cpp XalanElemEmptyAllocator.cpp \
	 XalanElemLiteralResultAllocator.cpp XalanElemTemplateAllocator.cpp \
	 XalanElemTextAllocator.cpp XalanElemTextLiteralAllocator.cpp \
	 XalanTemplate.cpp XalanElemValueOfAllocator.cpp \
	 XalanElemVariableAllocator.cpp XalanNumberingResourceBundle.cpp \
	 XalanSourceTreeDocumentAllocator.cpp \
	 XalanSourceTreeDocumentFragmentAllocator.cpp XalanSpaceNodeTester.cpp \
	 XalanAttr.cpp XalanCDataSection.cpp XalanCharacterData.cpp \
	 XalanComment.cpp XalanDOMException.cpp XalanDOMImplementation.cpp \
	 XalanDOMInit.cpp XalanDOMString.cpp XalanDocument.cpp \
	 XalanDocumentFragment.cpp XalanDocumentType.cpp XalanElement.cpp \
	 XalanEmptyNamedNodeMap.cpp XalanEntity.cpp XalanEntityReference.cpp \
	 XalanNamedNodeMap.cpp XalanNode.cpp XalanNodeList.cpp \
	 XalanNodeListDummy.cpp XalanNodeListSurrogate.cpp XalanNotation.cpp \
	 XalanProcessingInstruction.cpp XalanText.cpp XalanEXSLTCommon.cpp \
	 XalanEXSLTDateTime.cpp XalanEXSLTDynamic.cpp XalanEXSLTMath.cpp \
	 XalanEXSLTSet.cpp XalanEXSLTString.cpp FunctionDifference.cpp \
	 FunctionDistinct.cpp FunctionEvaluate.cpp FunctionHasSameNodes.cpp \
	 FunctionIntersection.cpp FunctionNodeSet.cpp XalanExtensions.cpp \
	 FormatterToSourceTree.cpp XalanSourceTreeAttr.cpp \
	 XalanSourceTreeAttrNS.cpp XalanSourceTreeAttributeAllocator.cpp \
	 XalanSourceTreeAttributeNSAllocator.cpp XalanSourceTreeComment.cpp \
	 XalanSourceTreeCommentAllocator.cpp XalanSourceTreeContentHandler.cpp \
	 XalanSourceTreeDOMSupport.cpp XalanSourceTreeDocument.cpp \
	 XalanSourceTreeDocumentFragment.cpp XalanSourceTreeElement.cpp \
	 XalanSourceTreeElementA.cpp XalanSourceTreeElementAAllocator.cpp \
	 XalanSourceTreeElementANS.cpp XalanSourceTreeElementANSAllocator.cpp \
	 XalanSourceTreeElementNA.cpp XalanSourceTreeElementNAAllocator.cpp \
	 XalanSourceTreeElementNANS.cpp XalanSourceTreeElementNANSAllocator.cpp \
	 XalanSourceTreeHelper.cpp XalanSourceTreeInit.cpp \
	 XalanSourceTreeParserLiaison.cpp \
	 XalanSourceTreeProcessingInstruction.cpp \
	 XalanSourceTreeProcessingInstructionAllocator.cpp \
	 XalanSourceTreeText.cpp XalanSourceTreeTextAllocator.cpp \
	 XalanSourceTreeTextIWS.cpp XalanSourceTreeTextIWSAllocator.cpp \
	 XalanCAPI.cpp XalanCompiledStylesheetDefault.cpp \
	 XalanDefaultDocumentBuilder.cpp XalanDefaultParsedSource.cpp \
	 XalanParsedSource.cpp XalanSourceTreeWrapperParsedSource.cpp \
	 XalanTransformer.cpp XalanTransformerOutputStream.cpp \
	 XalanTransformerProblemListener.cpp XercesDOMParsedSource.cpp \
	 XercesDOMWrapperParsedSource.cpp FormatterToXercesDOM.cpp \
	 XercesAttrWrapper.cpp XercesAttrWrapperAllocator.cpp \
	 XercesCDATASectionWrapper.cpp XercesCommentWrapper.cpp \
	 XercesDOMException.cpp XercesDOMFormatterWalker.cpp \
	 XercesDOMImplementationWrapper.cpp XercesDOMSupport.cpp \
	 XercesDOMWalker.cpp XercesDOMWrapperException.cpp \
	 XercesDocumentTypeWrapper.cpp XercesDocumentWrapper.cpp \
	 XercesEntityWrapper.cpp XercesElementWrapper.cpp \
	 XercesElementWrapperAllocator.cpp XercesEntityReferenceWrapper.cpp \
	 XercesLiaisonXalanDOMStringPool.cpp XercesNamedNodeMapAttributeList.cpp \
	 XercesParserLiaison.cpp FormatterToDeprecatedXercesDOM.cpp \
	 XercesAttrBridge.cpp XercesAttributeBridgeAllocator.cpp \
	 XercesBridgeHelper.cpp XercesBridgeNavigator.cpp \
	 XercesCDATASectionBridge.cpp XercesCommentBridge.cpp \
	 XercesDOMImplementationBridge.cpp XercesDOM_NodeHack.cpp \
	 XercesDocumentBridge.cpp XercesDocumentFragmentBridge.cpp \
	 XercesDocumentTypeBridge.cpp XercesElementBridge.cpp \
	 XercesElementBridgeAllocator.cpp XercesEntityBridge.cpp \
	 XercesEntityReferenceBridge.cpp XercesNamedNodeMapBridge.cpp \
	 XercesNodeListBridge.cpp XercesNotationBridge.cpp \
	 XercesProcessingInstructionBridge.cpp XercesTextBridge.cpp \
	 XercesTextBridgeAllocator.cpp XercesToXalanNodeMap.cpp \
	 XercesTreeWalker.cpp XercesNamedNodeMapWrapper.cpp \
	 XercesNodeListWrapper.cpp XercesNotationWrapper.cpp \
	 XercesProcessingInstructionWrapper.cpp XercesTextWrapper.cpp \
	 XercesTextWrapperAllocator.cpp XercesWrapperHelper.cpp \
	 XercesWrapperNavigator.cpp XercesWrapperToXalanNodeMap.cpp XalanExe.cpp
EXEBASE=Xalan
NEED_MATH=
BENCHLANG=CXX
ONESTEP=
CXXONESTEP=

BENCH_CXXFLAGS   = -DAPP_NO_THREADS -DXALAN_INMEM_MSG_LOADER -I. -Ixercesc -Ixercesc/dom -Ixercesc/dom/impl -Ixercesc/sax -Ixercesc/util/MsgLoaders/InMemory -Ixercesc/util/Transcoders/Iconv -Ixalanc/include -DPROJ_XMLPARSER -DPROJ_XMLUTIL -DPROJ_PARSERS -DPROJ_SAX4C -DPROJ_SAX2 -DPROJ_DOM -DPROJ_VALIDATORS -DXML_USE_NATIVE_TRANSCODER -DXML_USE_INMEM_MESSAGELOADER
CC               = /usr/bin/gcc
COPTIMIZE        = -O3 -fno-strict-aliasing
CXX              = /usr/bin/g++
CXXOPTIMIZE      = -O3 -fno-strict-aliasing
CXXPORTABILITY   = -DSPEC_CPU_LINUX
FC               = /usr/bin/gfortran
FOPTIMIZE        = -O3 -fno-strict-aliasing
FPBASE           = yes
OS               = unix
PORTABILITY      = -DSPEC_CPU_LP64
absolutely_no_locking = 0
abstol           = 
action           = validate
allow_extension_override = 0
backup_config    = 1
baseexe          = Xalan
basepeak         = 0
benchdir         = benchspec
benchmark        = 483.xalancbmk
binary           = 
bindir           = exe
build_in_build_dir = 1
builddir         = build
bundleaction     = 
bundlename       = 
calctol          = 0
changedmd5       = 0
check_integrity  = 0
check_md5        = 1
check_version    = 1
clcopies         = 1
command_add_redirect = 0
commanderrfile   = speccmds.err
commandexe       = Xalan_base.sniper-x86_64-gcc43
commandfile      = speccmds.cmd
commandoutfile   = speccmds.out
commandstdoutfile = speccmds.stdout
compareerrfile   = compare.err
comparefile      = compare.cmd
compareoutfile   = compare.out
comparestdoutfile = compare.stdout
compile_error    = 0
compwhite        = 
configdir        = config
configpath       = /scratch/tcarlson/cpu2006/config/linux64-sniper-x86_64-gcc43.cfg
copies           = 1
datadir          = data
delay            = 0
deletebinaries   = 0
deletework       = 0
difflines        = 10
dirprot          = 511
endian           = 12345678
env_vars         = 0
exitvals         = spec_exit
expand_notes     = 0
expid            = 
ext              = sniper-x86_64-gcc43
fake             = 1
feedback         = 1
flag_url_base    = http://www.spec.org/auto/cpu2006/flags/
floatcompare     = 
help             = 0
http_proxy       = 
http_timeout     = 30
hw_avail         = Dec-9999
hw_cpu_char      = 
hw_cpu_mhz       = 3000
hw_cpu_name      = AMD Opteron 256
hw_disk          = SATA
hw_fpu           = Integrated
hw_memory        = 2 GB (2 x 1GB DDR333 CL2.5)
hw_model         = Tyan Thunder KKQS Pro (S4882)
hw_nchips        = 1
hw_ncores        = 1
hw_ncoresperchip = 1
hw_ncpuorder     = 1 chip
hw_nthreadspercore = 1
hw_ocache        = None
hw_other         = None
hw_pcache        = 64 KB I + 64 KB D on chip per chip
hw_scache        = 1 MB I+D on chip per chip
hw_tcache        = None
hw_vendor        = Tyan
ignore_errors    = 0
ignore_sigint    = 0
ignorecase       = 
info_wrap_columns = 50
inputdir         = input
iteration        = -1
iterations       = 1
keeptmp          = 0
license_num      = 0
line_width       = 0
locking          = 1
log              = CPU2006
log_line_width   = 0
log_timestamp    = 0
logname          = /scratch/tcarlson/cpu2006/result/CPU2006.008.log
lognum           = 008
mach             = default
mail_reports     = all
mailcompress     = 0
mailmethod       = smtp
mailport         = 25
mailserver       = 127.0.0.1
mailto           = 
make             = specmake
make_no_clobber  = 0
makeflags        = 
max_active_compares = 0
mean_anyway      = 0
min_report_runs  = 3
minimize_builddirs = 0
minimize_rundirs = 0
name             = xalancbmk
need_math        = 
no_input_handler = close
no_monitor       = 
note_preenv      = 0
notes_wrap_columns = 0
notes_wrap_indent =   
num              = 483
obiwan           = 
os_exe_ext       = 
output           = asc
output_format    = asc
output_root      = 
outputdir        = output
parallel_setup   = 1
parallel_setup_prefork = 
parallel_setup_type = fork
parallel_test    = 0
parallel_test_submit = 0
path             = /scratch/tcarlson/cpu2006/benchspec/CPU2006/483.xalancbmk
plain_train      = 1
preenv           = 1
prefix           = 
prepared_by      = 
ranks            = 1
rate             = 0
realuser         = your name here
rebuild          = 1
reftime          = reftime
reltol           = 
reportable       = 0
resultdir        = result
review           = 0
run              = all
rundir           = run
runspec          = /scratch/tcarlson/cpu2006/bin/runspec -a run --fake all -c linux64-sniper-x86_64-gcc43.cfg
safe_eval        = 1
section_specifier_fatal = 1
sendmail         = /usr/sbin/sendmail
setpgrp_enabled  = 1
setprocgroup     = 1
shrate           = 0
sigint           = 2
size             = test
size_class       = test
skipabstol       = 
skipobiwan       = 
skipreltol       = 
skiptol          = 
smarttune        = base
specdiff         = specdiff
specmake         = Makefile.YYYtArGeTYYYspec
specrun          = specinvoke
speed            = 0
srcalt           = 
srcdir           = src
stagger          = 10
strict_rundir_verify = 1
sw_avail         = Mar-2008
sw_base_ptrsize  = 64-bit
sw_compiler      = gcc, g++ & gfortran 4.3.0 (for AMD64)
sw_file          = ext3
sw_os            = SUSE Linux Enterprise Server 10 (x86_64) SP1, Kernel 2.6.16.46-0.12-smp
sw_other         = None
sw_peak_ptrsize  = Not Applicable
sw_state         = Runlevel 3 (Full multiuser with network)
sysinfo_program  = 
table            = 1
teeout           = yes
teerunout        = yes
test_date        = Sep-2011
test_sponsor     = Turbo Computers
testaddedbytools3660 = 1
tester           = 
top              = /scratch/tcarlson/cpu2006
train_with       = train
trainaddedbytools3660 = 1
tune             = base
uid              = 10170
unbuffer         = 1
update-flags     = 0
use_submit_for_speed = 0
username         = tcarlson
vendor           = anon
vendor_makefiles = 0
verbose          = 5
version          = 0
version_url      = http://www.spec.org/auto/cpu2006/current_version
worklist         = list
OUTPUT_RMFILES   = train.out
