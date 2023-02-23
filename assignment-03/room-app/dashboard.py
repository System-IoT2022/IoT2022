import flet as ft


def main(page: ft.Page):
    page.title = "Flet counter example"
    page.vertical_alignment = ft.MainAxisAlignment.CENTER

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
            )
        
        ],
        alignment=ft.MainAxisAlignment.CENTER,
        )
        )
        


ft.app(target=main)