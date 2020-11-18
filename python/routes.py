from views import index, co2ampel_handler


def setup_routes(app):
    """Handle the routes."""
    app.router.add_get("/", index)
    app.router.add_post("/co2ampel", co2ampel_handler)
