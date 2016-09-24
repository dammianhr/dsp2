var JSONRPCClient; ///< The core JSONRPC WebSocket client.

function addError(error) {
    console.log(error);
}

function onWebSocketOpen(ws) {
    console.log("on open");
    console.log(ws);
}

function onWebSocketMessage(evt) {
    console.log("on message:");
    console.log(evt.data);
}

function onWebSocketClose() {
    console.log("on close");
}

function onWebSocketError() {
    console.log("on error");
}

function initializeButtons() {

    //Chanel MuteUnmute bind

    $('body').on('click', '.interactor.active',function(e) {
        e.preventDefault();
        console.log("mute");
        var $this = $(this);
        var $thisId = $this.parent().attr('id')
        JSONRPCClient.notify($thisId+'mute');
        getStatus($thisId);
    });


    $('body').on('click','.interactor.inactive', function(e) {
        e.preventDefault();
        console.log("unMute");
        var $this = $(this);
        var $thisId = $this.parent().attr('id')
        JSONRPCClient.notify($thisId+'unmute');
        getStatus($thisId);
    });


    //Chanel Distortion bind

    $('body').on('click', '.distortion.active',function(e) {
        e.preventDefault();
        console.log("mute");
        var $this = $(this);
        var $thisId = $this.parent().attr('id')
        JSONRPCClient.notify($thisId+'dis');
        getDistortionStatus($thisId);
    });


    $('body').on('click','.distortion.inactive', function(e) {
        e.preventDefault();
        console.log("unMute");
        var $this = $(this);
        var $thisId = $this.parent().attr('id')
        JSONRPCClient.notify($thisId+'und');
        getDistortionStatus($thisId);
    });



}

$(document).ready(function() {
    // Initialize our JSONRPCClient
    JSONRPCClient = new $.JsonRpcClient({
        ajaxUrl: getDefaultPostURL(),
        socketUrl: getDefaultWebSocketURL(), // get a websocket for the localhost
        onmessage: onWebSocketMessage,
        onopen: onWebSocketOpen,
        onclose: onWebSocketClose,
        onerror: onWebSocketError
    });

    initializeButtons();

    
 JSONRPCClient.call('getVol',
        null,
        function(result) {
                $('#ex1').val(result);
                var generalVolumen = $('#ex1').slider({
                    formatter: function(value) {
                        return value;
                    },
                    step: 3,
                    tooltip: 'always'

                }).on('slide', volumeChange);


        },
        function(error) {
            alert('ERROR: Mewito, Take a look the in JS console for more freacky details.');
            console.log('ERROR; '+ error);
        });


});

function getStatus(channel){
    var _channel = channel;
    var $this = $(this);

    JSONRPCClient.call(channel,
        null,
        function(result) {
            if(result == 1)
            {
                $('#'+_channel+' .interactor').removeClass('active inactive');
                $('#'+_channel+' .interactor').addClass('active');
            }
            else
            {
                $('#'+_channel+' .interactor').removeClass('active inactive');
                $('#'+_channel+' .interactor').addClass('inactive');
            }
        },
        function(error) {
            alert('ERROR; '+ error);
        });
}

function getDistortionStatus(channel){
    var _channel = channel;
    var $this = $(this);

    JSONRPCClient.call(channel+'d',
        null,
        function(result) {
            if(result == 1)
            {
                $('#'+_channel+' .interactor').removeClass('active inactive');
                $('#'+_channel+' .interactor').addClass('active');
            }
            else
            {
                $('#'+_channel+' .interactor').removeClass('active inactive');
                $('#'+_channel+' .interactor').addClass('inactive');
            }
        },
        function(error) {
            alert('ERROR; '+ error);
        });
}

function getVolStatus(channel){
    var _channel = channel;
    var $this = $(this);

    JSONRPCClient.call(channel+'vol',
        null,
        function(result) {
                $('#'+_channel+' .vol .status').css('width', (result)+'%');
        },
        function(error) {
            alert('ERROR; '+ error);
        });
}



// Get all channels and initialize status check
$('.chanel').each(function( index ) {

    var $this = $(this);
    var $thisId = $this.attr('id')


    setInterval(function(){
        if($this.find('.interactor').hasClass('active'))
        {
            getVolStatus($thisId);
        }
        getStatus($thisId);
    },500)


});



var volumeChange = function() {
    console.log('vol'+generalVolumen.val()); 
   JSONRPCClient.notify('vol'+generalVolumen.val()); 
};


