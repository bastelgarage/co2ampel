from views import co2ampel_handler, index, index_json


def setup_routes(app):
    """Handle the routes."""
    app.router.add_get("/", index)
    app.router.add_get("/json", index_json)
    app.router.add_post("/co2ampel", co2ampel_handler)
