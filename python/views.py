import hashlib
import time
import os

from aiohttp import web

sensors = {}


async def index(request):
    """Serve the content for the index."""
    return web.json_response(sensors)


async def co2ampel_handler(request):
    """Handle the HTTP Co2-Ampel requests."""
    parameters = await request.post()
    sensors[parameters["id"]] = {
        "timestamp": time.time(),
        "co2": parameters["c"],
        "temperature": parameters["t"],
        "humidity": parameters["h"],
        "brightness": parameters["l"],
    }

    return web.Response(text="post")
