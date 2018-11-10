import os
import tempfile
import time

#import threading
import microgear.client as microgear
import logging

from flask import Flask, jsonify, request, redirect, make_response, abort
import linecredential as linecred

from linebot import (
    LineBotApi, WebhookHandler
)
from linebot.exceptions import (
    InvalidSignatureError
)
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

import linehandletextmsg

# static_tmp_path = os.path.join(os.path.dirname(__file__), 'static', 'tmp')
static_tmp_path = os.path.join(os.path.dirname(__file__), 'tmp')

app = Flask(__name__)

uid_roona_joe_jj = "U4f3ca59bb9d158c184458043dcc4e339"

credentialLine = linecred.LineCredential.getCredential()
channel_access_token, channel_secret = linecred.LineCredential.extractCredential(
    credentialLine)
# print(channel_access_token)
# print(channel_secret)

line_bot_api = LineBotApi(channel_access_token)
handler = WebhookHandler(channel_secret)

##################################
appid = "napat"
gearkey = "264hMyPUmYSrXxN"
gearsecret = "2uA4SYXlPoA8Y2HtjNh7kbxz1"

aliasmy = "python01"

netpiefeedkey = "ZYgTt7VWnMvGtEtu3wkETXPIcpeiP02b"

microgear.create(gearkey, gearsecret,appid, {'debugmode': True})

###################################

@app.route('/', methods=['GET', 'POST'])
def hello():
    """Return a friendly HTTP greeting."""
    return '!!Hello World!!'


@app.errorhandler(500)
def server_error(e):
    logging.exception('An error occurred during a request.')
    return """
    An internal error occurred: <pre>{}</pre>
    See logs for full stacktrace.
    """.format(e), 500


@app.route("/callback", methods=['POST'])
def callback():
    # get X-Line-Signature header value
    signature = request.headers['X-Line-Signature']

    # get request body as text
    body = request.get_data(as_text=True)
    app.logger.info("Request body: " + body)

    # handle webhook body
    try:
        handler.handle(body, signature)
    except InvalidSignatureError:
        abort(400)

    return 'OK'

@handler.add(MessageEvent, message=TextMessage)
def handle_message(event):

    #print('----')
    #print(event)
    
    # https://github.com/line/line-bot-sdk-python/blob/master/linebot/models/events.py
    txtmsg = event.message.text
    replyToken = event.reply_token
    userId = event.source.user_id

    linehandletextmsg.linehandle_txtmsg(microgear, line_bot_api, event, txtmsg, replyToken, userId)


@handler.add(MessageEvent, message=(ImageMessage, VideoMessage, AudioMessage))
def handle_content_message(event):
    if isinstance(event.message, ImageMessage):
        ext = 'jpg'
    elif isinstance(event.message, VideoMessage):
        ext = 'mp4'
    elif isinstance(event.message, AudioMessage):
        ext = 'm4a'
    else:
        return

    print(static_tmp_path)

    message_content = line_bot_api.get_message_content(event.message.id)
    with tempfile.NamedTemporaryFile(dir=static_tmp_path, prefix=ext + '-', delete=False) as tf:
        for chunk in message_content.iter_content():
            tf.write(chunk)
        tempfile_path = tf.name

    dist_path = tempfile_path + '.' + ext
    dist_name = os.path.basename(dist_path)
    os.rename(tempfile_path, dist_path)

    line_bot_api.reply_message(
        event.reply_token, [
            TextSendMessage(text='Save content.'),
            TextSendMessage(text=request.host_url +
                            os.path.join('static', 'tmp', dist_name))
        ])


@handler.add(BeaconEvent)
def linehandle_beacon(event):
    # print('...............1')
    # print(event)
    # print('...............2')

    # Reply tokens can only be used once.

    # basic text msg
    '''
    line_bot_api.reply_message(
        event.reply_token,
        TextSendMessage(
            text=f'Got beacon event. hwid={event.beacon.hwid}, device_message(hex string)={event.beacon.dm}'
        ) 
    ) 
    '''

    # msg bubble, more info: https://github.com/line/line-bot-sdk-python/blob/master/examples/flask-kitchensink/app.py
    bubble = BubbleContainer(
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
                        TextComponent(text='4.0', size='sm', color='#999999', margin='md',
                                      flex=0)
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
                                    text=f'{event.beacon.hwid}',
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
                                    text=f'{event.beacon.dm}',
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

    message = FlexSendMessage(alt_text="RooNa Cafe", contents=bubble)
    line_bot_api.reply_message(
        event.reply_token,
        message
    )


def connection():
    logging.info("Now I am connected with netpie")

def subscription(topic, message):
    logging.info(topic+"----->"+message)

    if '/napat/linemails' in topic:
        if 'เร่งแอร์หน่อยมั้ย' in message:
            line_bot_api.push_message(uid_roona_joe_jj, TextSendMessage(text=message))
            replymsg = StickerSendMessage(package_id=2, sticker_id=27)
            line_bot_api.push_message(uid_roona_joe_jj, replymsg)
        else:
            line_bot_api.push_message(uid_roona_joe_jj, TextSendMessage(text=message))

def disconnect():
    logging.info("disconnected")

def writefeed():
    data = int(time.time()) % 10
    feeddat = {
        "var1": data,
        "var2": (data-1)*10,
        "var3": (data+5)*20,
    }
    microgear.writeFeed("feed0001", feeddat, feedkey=netpiefeedkey)



if __name__ == "__main__":

    microgear.setalias(aliasmy)
    microgear.on_connect = connection
    microgear.on_message = subscription
    microgear.on_disconnect = disconnect
    microgear.subscribe("/linemails", qos=0)
    microgear.connect(False)

    app.run(host='0.0.0.0', debug=False, port=int(os.environ.get('PORT', '5000')))
    print('end')
