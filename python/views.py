import hashlib
import os
import time

import aiohttp_jinja2
from aiohttp import web

sensors = {}


@aiohttp_jinja2.template("index.html")
async def index(request):
    """Serve the content for the index."""
    return {"sensors": sensors}


async def index_json(request):
    """Serve the content as JSON."""
    return web.json_response(sensors)


async def co2ampel_handler(request):
    """Handle the HTTP CO2-Ampel requests."""
    parameters = await request.post()
    sensors[parameters["id"]] = {
        "timestamp": time.time(),
        "co2": parameters["c"],
        "temperature": parameters["t"],
        "humidity": parameters["h"],
        "brightness": parameters["l"],
    }

    return web.Response(text="post")
