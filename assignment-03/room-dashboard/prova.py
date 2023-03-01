import plotly.express as px
import flet as ft
from flet.plotly_chart import PlotlyChart
import plotly.graph_objs as go

def main(page: ft.Page):

    chartData = {"x":["1","2","3"], "y":["1","2","3"]}
    fig = go.FigureWidget(go.Scatter(x=chartData['x'], y=chartData['y']))
    chart = PlotlyChart(fig, expand=True)
    page.add(chart)
    
    page.remove(chart)
    chartData = {"x":["11:22:3", "11:23:3","11:24:3","11:25:3","11:26:3"], "y":["on","on","off","off","on"]}
    fig = go.FigureWidget(go.Scatter(x=chartData['x'], y=chartData['y']))
    chart = PlotlyChart(fig, expand=True)
    #chart.update() # update chart with new data
    page.add(chart)
    
    #page.update() # call page.update() after updating the chart

ft.app(target=main)
