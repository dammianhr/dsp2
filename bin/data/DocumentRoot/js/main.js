var JSONRPCClient; ///< The core JSONRPC WebSocket client.

var configIsOpen = 'false';

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

    $('body').on('change', '#ex1',function(e) {
        e.preventDefault();
        console.log("Change the general volume to:", $('#ex1').val());
        JSONRPCClient.notify('vol'+$('#ex1').val()); 

    });

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
        console.log("Distortion");
        var $this = $(this);
        var $thisId = $this.parent().attr('id')
        JSONRPCClient.notify('c'+$thisId+'dis');
        getDistortionStatus($thisId);
    });


    $('body').on('click','.distortion.inactive', function(e) {
        e.preventDefault();
        console.log("UnDisturtion");
        var $this = $(this);
        var $thisId = $this.parent().attr('id')
        JSONRPCClient.notify('c'+$thisId+'und');
        getDistortionStatus($thisId);
    });


    // Confing page manager

    $('body').on('click','#openConfig', function(e) {
        e.preventDefault();
        console.log("Open Config");

        $('.front').fadeOut();
        $('.back').fadeIn();
        
        configIsOpen = true;
    });
    $('body').on('click','#closeConfig', function(e) {
        e.preventDefault();
        console.log("Close Config");

        $('.front').fadeIn();
        $('.back').fadeOut();
        
        configIsOpen = false;
    });


    //Config input bind


        $('body').on('focusout click','.eqcontrol', function(e) {
           // e.preventDefault();

            var $this = $(this);
            var $thisBand = $this.attr('banda');
            var $thisBypass = 0;

            if($('input.bypass[banda='+$thisBand+']').is(':checked'))
            {
                $thisBypass = 1;
            }
            else
            {
                $thisBypass = 0;
            }

            console.log($thisBand+'_'+$('input.freq[banda='+$thisBand+']').val()+'_'+$('input.qfactor[banda='+$thisBand+']').val()+'_'+$('input.boost[banda='+$thisBand+']').val()+'_'+$thisBypass);

            JSONRPCClient.call('setEq',
            $thisBand+'_'+$('input.freq[banda='+$thisBand+']').val()+'_'+$('input.qfactor[banda='+$thisBand+']').val()+'_'+$('input.boost[banda='+$thisBand+']').val()+'_'+$thisBypass ,
            function(result) {
                    console.log(result);
            },
            function(error) {
                alert('ERROR; '+ error);
            });

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

    getGeneralVolume();


});


function getGeneralVolume()
{

     JSONRPCClient.call('getVol',
        null,
        function(result) {
                $('#ex1').val(result);
                


        },
        function(error) {
            alert('ERROR: Mewito, Take a look the in JS console for more freacky details.');
            console.log('ERROR; '+ error);
        });


}

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

    JSONRPCClient.call('c'+channel+'d',
        null,
        function(result) {
            if(result == 1)
            {
                $('#'+_channel+' .distortion').removeClass('active inactive');
                $('#'+_channel+' .distortion').addClass('active');
            }
            else
            {
                $('#'+_channel+' .distortion').removeClass('active inactive');
                $('#'+_channel+' .distortion').addClass('inactive');
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
        if($this.find('.interactor').hasClass('active') && !configIsOpen)
        {
            getVolStatus($thisId);
        }
        getStatus($thisId);
    },500)


});
