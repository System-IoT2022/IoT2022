#!/usr/bin/python 

import flet as ft
import plotly.express as pl
import json 
import pandas as pd
from flet.plotly_chart import PlotlyChart

#from client.py import *

chartData = {"x":["11:22:3", "11:23:3","11:24:3","11:25:3","11:26:3"], "y":["on","on","off","off","on"]} #dictionary
def parseMessage(data): #load recived data 
        parsed = json.load(data)
        for state in parsed['Received']:
               chartData['x'] = state[0]
               chartData['y'] = state[1]

fig=pl.line(x=chartData['x'],y=chartData['y'])


def buildGui(page: ft.page):      
        btn0 = ft.ElevatedButton("switch on")
        btn1 = ft.ElevatedButton("switch off")
        slider = ft.Slider(min=0, max=100, divisions=10, rotate=1.57) 
        text0= ft.Text("Light")
        text1=ft.Text("Curtain")
        
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
                PlotlyChart(fig, expand=True)
            
            ],
            alignment=ft.MainAxisAlignment.CENTER,
            )
            )

if __name__ == '__main__':
      ft.app(target=buildGui)