from linebot.models import (
    MessageEvent, TextMessage, TextSendMessage,
    SourceUser, SourceGroup, SourceRoom,
    TemplateSendMessage, ConfirmTemplate, MessageAction,
    ButtonsTemplate, ImageCarouselTemplate, ImageCarouselColumn, URIAction,
    PostbackAction, DatetimePickerAction,
    CameraAction, CameraRollAction, LocationAction,
    CarouselTemplate, CarouselColumn, PostbackEvent,
    StickerMessage, StickerSendMessage, LocationMessage, LocationSendMessage,
    ImageMessage, ImageSendMessage, VideoMessage, AudioMessage, FileMessage,
    UnfollowEvent, FollowEvent, JoinEvent, LeaveEvent, BeaconEvent,
    FlexSendMessage, BubbleContainer, ImageComponent, BoxComponent,
    TextComponent, SpacerComponent, IconComponent, ButtonComponent,
    SeparatorComponent, QuickReply, QuickReplyButton, CarouselContainer
)

import json
import random
from jinja2 import Environment, FileSystemLoader, select_autoescape

uid_roona_joe_jj = "U4f3ca59bb9d158c184458043dcc4e339"

template_env = Environment(
    loader=FileSystemLoader('templates'),
    autoescape=select_autoescape(['html', 'xml', 'json'])
)

def linehandle_txtmsg(line_bot_api, event, txtmsg, replyToken, userId):
    # print(f'msg: {txtmsg} / {txtmsg} / {replyToken} / {userId}')
    '''
    line_bot_api.reply_message(
        replyToken, TextSendMessage(text=event.message.text))

    line_bot_api.push_message(
        uid_roona_joe_jj, TextSendMessage(text='Hello World!'))
    '''

    if(isgreeting(line_bot_api, event, txtmsg, replyToken, userId) == True):
        return True
    
    if(isknownintent(line_bot_api, event, txtmsg, replyToken, userId) == True):
        return True

    if(isknownintentsample(line_bot_api, event, txtmsg, replyToken, userId) == True):
        return True

    replymsg = f"RooNa ไม่เข้าใจว่า {txtmsg} หมายถึงอะไร"
    line_bot_api.reply_message(replyToken, TextSendMessage(text=replymsg))
    return False


# Sentences we'll respond with if the user greeted us
GREETING_KEYWORDS = ("hello", "hi", "greetings", "sup", "what's up", "ขอมือหน่อย", "สวัสดี")

GREETING_RESPONSES = ["'sup bro", "hey", "*nods*", "hey you get my snap?"]


def isgreeting(line_bot_api, event, txtmsg, replyToken, userId):
    """If any of the words in the user's input was a greeting, return True"""
    for word in txtmsg.split(" "):
        if word.lower() in GREETING_KEYWORDS:
            replymsg = random.choice(GREETING_RESPONSES)
            line_bot_api.reply_message(
                replyToken, TextSendMessage(text=replymsg))
            return True
        else:
            # "not found"
            return False

def isknownintent(line_bot_api, event, txtmsg, replyToken, userId):
    if "menu" in txtmsg.lower():
        template = template_env.get_template('carouselcontroller.json')
        myjson = json.loads( template.render())
        replysticker = FlexSendMessage(
            alt_text='user',
            contents=CarouselContainer.new_from_json_dict(myjson)
        )
        line_bot_api.reply_message(replyToken, replysticker)
        return True
    
    return False


######################## zone example ##########################
def isknownintentsample(line_bot_api, event, txtmsg, replyToken, userId):

    if "กินอะไร" in txtmsg or "หิว" in txtmsg:
        replymsg = "กินข้าวไข่เจียว"
        line_bot_api.reply_message(replyToken, TextSendMessage(text=replymsg))
        return True

    if "เปิดไฟ" in txtmsg.lower():
        if "หน้าบ้าน" in txtmsg.lower():
            replymsg = "เปิดเรียบร้อยครับท่าน"
            line_bot_api.reply_message(
                replyToken, TextSendMessage(text=replymsg))
            return True
        elif "ในครัว" in txtmsg.lower():
            replymsg = "เปิดเรียบร้อยครับท่าน"
            line_bot_api.reply_message(
                replyToken, TextSendMessage(text=replymsg))
            return True
        else:
            replymsg = "ระบุตำแหน่งเช่น หน้าบ้าน/ในครัว ด้วยครับ"
            line_bot_api.reply_message(
                replyToken, TextSendMessage(text=replymsg))
            return True

    if "ปิดไฟ" in txtmsg.lower():
        if "หน้าบ้าน" in txtmsg.lower():
            replymsg = "ปิดเรียบร้อยครับท่าน"
            line_bot_api.reply_message(
                replyToken, TextSendMessage(text=replymsg))
            return True
        elif "ในครัว" in txtmsg.lower():
            replymsg = "ปิดเรียบร้อยครับท่าน"
            line_bot_api.reply_message(
                replyToken, TextSendMessage(text=replymsg))
            return True
        else:
            replymsg = "ระบุตำแหน่งเช่น หน้าบ้าน/ในครัว ด้วยครับ"
            line_bot_api.reply_message(
                replyToken, TextSendMessage(text=replymsg))
            return True

    # sticker: https://devdocs.line.me/files/sticker_list.pdf
    if "เหนื่อยจัง" in txtmsg.lower():
        replysticker = StickerSendMessage(package_id=2, sticker_id=47)
        line_bot_api.reply_message(replyToken, replysticker)
        return True

    # image : ImageSendMessage
    if "ขอรูปหน่อย" in txtmsg.lower():
        replysticker = ImageSendMessage(
            preview_image_url='https://vignette.wikia.nocookie.net/disney/images/5/52/Roo_Winnie_the_Pooh.jpg',
            original_content_url='https://vignette.wikia.nocookie.net/disney/images/f/f5/Tigger-movie-disneyscreencaps.com-2583.jpg'
        )
        line_bot_api.reply_message(replyToken, replysticker)
        return True

    # QuickReply & QuickReplyButton
    if "ตัวอย่างQuickReply" in txtmsg.lower():
        replysticker = TextSendMessage(
            text='Hello, world',
            quick_reply=QuickReply(items=[
            QuickReplyButton(
                image_url='https://golang.org/doc/gopher/help.png',
                action=PostbackAction(
                    label="txData", data="myData")
            ),
            QuickReplyButton(
                action=MessageAction(
                    label="txText", text="myText")
            ),
            QuickReplyButton(
                action=DatetimePickerAction(label="SelectDate",
                                            data="data3",
                                            mode="date")
            ),
            QuickReplyButton(
                action=CameraAction(
                    label="SelectCamera")
            ),
            QuickReplyButton(
                action=CameraRollAction(
                    label="SelectImage")
            ),
            QuickReplyButton(
                action=LocationAction(
                    label="Selectlocation")
            ),
        ]))
        line_bot_api.reply_message(replyToken, replysticker)
        return True

    # flex: https://developers.line.me/en/docs/messaging-api/flex-message-elements/

    # flex: bubble code struct
    if "roona" in txtmsg.lower() and "cafe" in txtmsg.lower():
        send_bubble_example(line_bot_api, event, txtmsg, replyToken, userId)
        return True

    # flex: json bubble
    if "flex json bubble example" in txtmsg.lower():

        """ 
        user = ''
        items = ''

        template = template_env.get_template('user.json')
        data = template.render(dict(user=user, items=items)) 
        """

        template = template_env.get_template('bubble01.json')
        myjson = json.loads( template.render())
        replysticker = FlexSendMessage(
            alt_text='user',
            contents=BubbleContainer.new_from_json_dict(myjson)
        )
        line_bot_api.reply_message(replyToken, replysticker)
        return True

    # flex: json carousel
    if "flex json carousel controller" in txtmsg.lower():
        template = template_env.get_template('carouselcontroller.json')
        myjson = json.loads( template.render())
        replysticker = FlexSendMessage(
            alt_text='user',
            contents=CarouselContainer.new_from_json_dict(myjson)
        )
        line_bot_api.reply_message(replyToken, replysticker)
        return True
    
    return False


def send_bubble_example(line_bot_api, event, txtmsg, replyToken, userId):
    # msg bubble, more info: https://github.com/line/line-bot-sdk-python/blob/master/examples/flask-kitchensink/app.py
    bubble=BubbleContainer(
        direction='ltr',
        hero=ImageComponent(
            url='https://scdn.line-apps.com/n/channel_devcenter/img/fx/01_1_cafe.png',
            size='full',
            aspect_ratio='20:13',
            aspect_mode='cover',
            action=URIAction(
                uri='https://www.google.co.th/search?q=cafe', label='label')
        ),
        body=BoxComponent(
            layout='vertical',
            contents=[
                # title
                TextComponent(text='RooNa Cafe', weight='bold', size='xl'),
                # review
                BoxComponent(
                    layout='baseline',
                    margin='md',
                    contents=[
                        IconComponent(
                            size='sm', url='https://scdn.line-apps.com/n/channel_devcenter/img/fx/review_gold_star_28.png'),
                        IconComponent(
                            size='sm', url='https://scdn.line-apps.com/n/channel_devcenter/img/fx/review_gold_star_28.png'),
                        IconComponent(
                            size='sm', url='https://scdn.line-apps.com/n/channel_devcenter/img/fx/review_gold_star_28.png'),
                        IconComponent(
                            size='sm', url='https://scdn.line-apps.com/n/channel_devcenter/img/fx/review_gold_star_28.png'),
                        IconComponent(
                            size='sm', url='https://scdn.line-apps.com/n/channel_devcenter/img/fx/review_gray_star_28.png'),
                        TextComponent(text='4.0', size='sm',
                                      color='#999999', margin='md', flex=0)
                    ]
                ),
                # info
                BoxComponent(
                    layout='vertical',
                    margin='lg',
                    spacing='sm',
                    contents=[
                        BoxComponent(
                            layout='baseline',
                            spacing='sm',
                            contents=[
                                TextComponent(
                                    text='Place',
                                    color='#aaaaaa',
                                    size='sm',
                                    flex=1
                                ),
                                TextComponent(
                                    text='Bangkok, Thailand',
                                    wrap=True,
                                    color='#666666',
                                    size='sm',
                                    flex=5
                                )
                            ],
                        ),
                        BoxComponent(
                            layout='baseline',
                            spacing='sm',
                            contents=[
                                TextComponent(
                                    text='Time',
                                    color='#aaaaaa',
                                    size='sm',
                                    flex=1
                                ),
                                TextComponent(
                                    text="10:00 - 23:00",
                                    wrap=True,
                                    color='#666666',
                                    size='sm',
                                    flex=5,
                                ),
                            ],
                        ),
                        BoxComponent(
                            layout='baseline',
                            spacing='sm',
                            contents=[
                                TextComponent(
                                    text='Beacon ID',
                                    color='#aaaaaa',
                                    size='sm',
                                    flex=2
                                ),
                                TextComponent(
                                    # f'{event.beacon.hwid}',
                                    text='{event.beacon.hwid}',
                                    wrap=True,
                                    color='#666666',
                                    size='sm',
                                    flex=4
                                )
                            ],
                        ),
                        BoxComponent(
                            layout='baseline',
                            spacing='sm',
                            contents=[
                                TextComponent(
                                    text='Device msg',
                                    color='#aaaaaa',
                                    size='sm',
                                    flex=2
                                ),
                                TextComponent(
                                    # f'{event.beacon.dm}',
                                    text='{event.beacon.dm}',
                                    wrap=True,
                                    color='#666666',
                                    size='sm',
                                    flex=4
                                )
                            ],
                        ),
                    ],
                )
            ],
        ),
        footer=BoxComponent(
            layout='vertical',
            spacing='sm',
            contents=[
                # callAction, separator, websiteAction
                SpacerComponent(size='sm'),
                # callAction
                ButtonComponent(
                    style='link',
                    height='sm',
                    action=URIAction(label='CALL', uri='tel:000000'),
                ),
                # separator
                SeparatorComponent(),
                # websiteAction
                ButtonComponent(
                    style='link',
                    height='sm',
                    action=URIAction(
                        label='WEBSITE', uri="https://example.com")
                )
            ]
        ),
    )

    message=FlexSendMessage(alt_text="RooNa Cafe", contents=bubble)
    line_bot_api.reply_message(
        event.reply_token,
        message
    )
