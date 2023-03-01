#!/usr/bin/python 

import flet as ft
import plotly.express as pl
import json 
import pandas as pd
from flet.plotly_chart import PlotlyChart
from client import MsgClient
import socket
import plotly.graph_objs as go

#from client.py import *

PORT = 12345
msgClient = MsgClient(PORT, socket.gethostname())
chartData = {"x":["11:22:3", "11:23:3","11:24:3","11:25:3","11:26:3"], "y":["on","on","off","off","on"]} #dictionary

'''def parseMessage(data): #load recived data 
    parsed = json.load(data)
    for state in parsed['Received']:
            chartData['x'] = state[0]
            chartData['y'] = state[1]'''

def parseMessage2(data_str):
    data = json.loads(data_str)
    times = []
    states = []
    for item in data:
        parts = item.split()
        times.append(parts[0])
        states.append(parts[1])
    return {"x":times, "y":states}


def createChart(chartData):
    return PlotlyChart(go.FigureWidget(go.Scatter(x=chartData['x'], y=chartData['y'])), expand=True, isolated=True)
def createFigure(charData):
     go.FigureWidget(go.Scatter(x=chartData['x'], y=chartData['y']))

chart = createChart(chartData)

def buildGui(page: ft.page):      
        btn0 = ft.ElevatedButton("switch on")
        btn1 = ft.ElevatedButton("switch off")
        btnUpdate = ft.ElevatedButton("update graph")
        slider = ft.Slider(min=0, max=100, divisions=10, rotate=1.57) 
        text0= ft.Text("Light")
        text1=ft.Text("Curtain")

        def update_graph_callback(widget):
            # Here you would define the code to update the graph
            global chart
            chartData = msgClient.send_message('0')
            chartData = parseMessage2(chartData)
            chartData = {'x':[1,2,3], 'y':[2,3,4]}
            print(chartData)
            chart.figure = createFigure(chartData)
            chart.update()
            page.update()
            print("graph updated")
    
        btnUpdate.on_click = update_graph_callback
        
        iconLight= ft.Icon(name=ft.icons.LIGHTBULB_OUTLINED, color=ft.colors.YELLOW)
        page.add(
            ft.Row(
            [        
                ft.Column(
                [      
                    ft.Column(
                    [                
                        text0,
                        btn0,
                        btn1,
                        btnUpdate,
                        iconLight
                    ],
                    spacing=20,
                    #alignment=ft.MainAxisAlignment.CENTER,
                    ),

                    ft.Column(
                    [
                        text1,
                        slider
                    ],
                    #alignment=ft.MainAxisAlignment.CENTER,
                    )
                ],
                spacing=90,
                ),
                chart
            
            ],
            alignment=ft.MainAxisAlignment.CENTER,
            )
            )

if __name__ == '__main__':
      ft.app(target=buildGui)